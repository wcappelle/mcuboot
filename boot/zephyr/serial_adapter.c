/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <uart.h>
#include <assert.h>
#include <string.h>
#include <zephyr.h>

#ifdef CONFIG_UART_CONSOLE
#error Zephyr UART console must been disabled if serial_adapter module is used.
#endif

/** @brief Console input representation
 *
 * This struct is used to represent an input line from a serial interface.
 */
struct line_input {
	/** Required to use sys_slist */
	sys_snode_t node;

	int len;
	/** Buffer where the input line is recorded */
	char line[CONFIG_BOOT_MAX_LINE_INPUT_LEN];
};

static struct device *uart_dev;
static struct line_input line_bufs[2];

static sys_slist_t free_queue;
static sys_slist_t used_queue;

static sys_slist_t *avail_queue;
static sys_slist_t *lines_queue;
static u16_t cur;

static int boot_uart_fifo_getline(char **line);
static int boot_uart_fifo_init(void);

int
console_out(int c)
{
	uart_poll_out(uart_dev, c);

	return c;
}

void
console_write(const char *str, int cnt)
{
	int i;

	for (i = 0; i < cnt; i++) {
		if (console_out((int)str[i]) == EOF) {
			break;
		}
	}
}

int
console_read(char *str, int str_size, int *newline)
{
	char *line;
	int len;

	len = boot_uart_fifo_getline(&line);

	if (line == NULL) {
		*newline = 0;
		return 0;
	}

	if (len > str_size - 1) {
		len = str_size - 1;
	}

	memcpy(str, line, len);
	str[len] = '\0';
	*newline = 1;
	return len + 1;
}

int
boot_console_init(void)
{
	int i;

	sys_slist_init(&free_queue);
	sys_slist_init(&used_queue);

	for (i = 0; i < ARRAY_SIZE(line_bufs); i++) {
		sys_slist_append(&free_queue, &line_bufs[i].node);
	}

	/* Zephyr UART handler takes an empty buffer from free_queue,
	 * stores UART input in it until EOL, and then puts it into
	 * used_queue.
	 */
	avail_queue = &free_queue;
	lines_queue = &used_queue;

	return boot_uart_fifo_init();
}

static void
boot_uart_fifo_callback(struct device *dev)
{
	static struct line_input *cmd;
	u8_t byte;
	int rx;

	while (uart_irq_update(uart_dev) &&
	       uart_irq_rx_ready(uart_dev)) {

		rx = uart_fifo_read(uart_dev, &byte, 1);
		if (rx != 1) {
			continue;
		}

		if (!cmd) {
			sys_snode_t *node;

			node = sys_slist_get(avail_queue);
			if (!node) {
				return;
			}
			cmd = CONTAINER_OF(node, struct line_input, node);
		}

		if (cur < CONFIG_BOOT_MAX_LINE_INPUT_LEN) {
			cmd->line[cur++] = byte;
		}

		if (byte ==  '\n') {
			cmd->len = cur;
			sys_slist_append(lines_queue, &cmd->node);
			cur = 0;
		}
	}
}

static int
boot_uart_fifo_getline(char **line)
{
	static struct line_input *cmd;
	sys_snode_t *node;

	/* Recycle cmd buffer returned previous time */
	if (cmd != NULL) {
		sys_slist_append(&free_queue, &cmd->node);
	}

	node = sys_slist_get(&used_queue);

	if (node == NULL) {
		cmd = NULL;
		*line = NULL;
		return 0;
	}

	cmd = CONTAINER_OF(node, struct line_input, node);
	*line = cmd->line;
	return cmd->len;
}

static int
boot_uart_fifo_init(void)
{
	uart_dev = device_get_binding(CONFIG_UART_CONSOLE_ON_DEV_NAME);
	u8_t c;

	if (!uart_dev) {
		return (-1);
	}

	uart_irq_callback_set(uart_dev, boot_uart_fifo_callback);

	/* Drain the fifo */
	while (uart_irq_rx_ready(uart_dev)) {
		uart_fifo_read(uart_dev, &c, 1);
	}

	cur = 0;

	uart_irq_rx_enable(uart_dev);

	/* Enable all interrupts unconditionally. Note that this is due
	 * to Zephyr issue #8393. This should be removed once the
	 * issue is fixed in upstream Zephyr. */
	irq_unlock(0);

	return 0;
}
