/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <bootutil/sign_key.h>

/*
 * Even though this is in principle a Zephyr-specific file, the
 * simulator builds it and uses it as well. Because of that, we can't
 * use Kconfig symbols for key types, and have to rely on the MCUBoot
 * symbols (which Zephyr provides via this header, and the simulator
 * provides via the compiler command line).
 */
#include <mcuboot_config/mcuboot_config.h>

#if !defined(MCUBOOT_HW_KEY)
#if defined(MCUBOOT_SIGN_RSA)
#define HAVE_KEYS
extern const unsigned char rsa_pub_key[];
extern unsigned int rsa_pub_key_len;
#elif defined(MCUBOOT_SIGN_EC256)
#define HAVE_KEYS
extern const unsigned char ecdsa_pub_key[];
extern unsigned int ecdsa_pub_key_len;
#elif defined(MCUBOOT_SIGN_ED25519)
#define HAVE_KEYS
extern const unsigned char ed25519_pub_key[];
extern unsigned int ed25519_pub_key_len;
#endif

/*
 * NOTE: *_pub_key and *_pub_key_len are autogenerated based on the provided
 *       key file. If no key file was configured, the array and length must be
 *       provided and added to the build manually.
 */
#if defined(HAVE_KEYS)
const struct bootutil_key bootutil_keys[] = {
    {
#if defined(MCUBOOT_SIGN_RSA)
        .key = rsa_pub_key,
        .len = &rsa_pub_key_len,
#elif defined(MCUBOOT_SIGN_EC256)
        .key = ecdsa_pub_key,
        .len = &ecdsa_pub_key_len,
#elif defined(MCUBOOT_SIGN_ED25519)
        .key = ed25519_pub_key,
        .len = &ed25519_pub_key_len,
#endif
    },
};
const int bootutil_key_cnt = 1;
#endif /* HAVE_KEYS */
#else
unsigned int pub_key_len;
struct bootutil_key bootutil_keys[1] = {
    {
        .key = 0,
        .len = &pub_key_len,
    }
};
const int bootutil_key_cnt = 1;
#endif /* !MCUBOOT_HW_KEY */

#if defined(MCUBOOT_ENCRYPT_RSA)
unsigned char enc_priv_key[] = {
  0x30, 0x82, 0x04, 0xa4, 0x02, 0x01, 0x00, 0x02, 0x82, 0x01, 0x01, 0x00,
  0xb4, 0x26, 0x14, 0x49, 0x3d, 0x16, 0x13, 0x3a, 0x6d, 0x9c, 0x84, 0xa9,
  0x8b, 0x6a, 0x10, 0x20, 0x61, 0xef, 0x48, 0x04, 0xa4, 0x4b, 0x24, 0xf3,
  0x00, 0x32, 0xac, 0x22, 0xe0, 0x30, 0x27, 0x70, 0x18, 0xe5, 0x55, 0xc8,
  0xb8, 0x05, 0x34, 0x03, 0xb0, 0xf8, 0xa5, 0x96, 0xd2, 0x48, 0x58, 0xef,
  0x70, 0xb0, 0x09, 0xdb, 0xe3, 0x58, 0x62, 0xef, 0x99, 0x63, 0x01, 0xb2,
  0x89, 0xc4, 0xb3, 0xf6, 0x9e, 0x62, 0xbf, 0x4d, 0xc2, 0x8a, 0xd0, 0xc9,
  0x4d, 0x43, 0xa3, 0xd8, 0xe5, 0x1d, 0xec, 0x62, 0x63, 0x08, 0xe2, 0x20,
  0xa5, 0xfc, 0x78, 0xd0, 0x3e, 0x74, 0xc8, 0xa4, 0x1b, 0x36, 0xad, 0x7b,
  0xf5, 0x06, 0xae, 0x4d, 0x51, 0x9b, 0x40, 0xce, 0x30, 0x4f, 0x6c, 0xea,
  0xf9, 0xe9, 0x74, 0xea, 0x06, 0xee, 0x9c, 0xe4, 0x14, 0x68, 0x20, 0xb9,
  0x3d, 0xe7, 0x11, 0x14, 0x8b, 0x25, 0xa3, 0xff, 0x4c, 0x8a, 0xf3, 0x53,
  0xee, 0x6b, 0x3e, 0xef, 0x34, 0xcd, 0x6a, 0x3f, 0x62, 0x68, 0xc0, 0xff,
  0x78, 0x4c, 0xb0, 0xc3, 0xe6, 0x96, 0x61, 0xfc, 0x1f, 0x18, 0xf1, 0x7a,
  0x82, 0xe2, 0x8f, 0x35, 0xa8, 0x2b, 0x86, 0x16, 0xa4, 0x46, 0xfb, 0xac,
  0x7e, 0x41, 0xdb, 0x02, 0x05, 0x91, 0x6d, 0xdf, 0xc1, 0xde, 0x13, 0x95,
  0x9c, 0xf9, 0x9e, 0x5e, 0x72, 0xba, 0xa7, 0x25, 0x93, 0xfb, 0xdc, 0xe8,
  0xab, 0x86, 0x45, 0x88, 0x47, 0x2d, 0xed, 0xee, 0xee, 0x97, 0x9e, 0xce,
  0x5d, 0x9b, 0x04, 0x04, 0x40, 0x7c, 0xcb, 0x7c, 0x3d, 0x2c, 0x74, 0xab,
  0xa4, 0xcc, 0x64, 0xa3, 0x5c, 0x95, 0x3d, 0xd4, 0xa2, 0xdc, 0x92, 0xb2,
  0xc8, 0x18, 0xcb, 0xf9, 0x00, 0x39, 0x81, 0x8f, 0x8f, 0x40, 0xc2, 0xdf,
  0x99, 0x29, 0xac, 0x8a, 0xc2, 0x3b, 0xd8, 0xa4, 0xf2, 0xad, 0xaf, 0x74,
  0xc0, 0x11, 0xc7, 0x99, 0x02, 0x03, 0x01, 0x00, 0x01, 0x02, 0x82, 0x01,
  0x00, 0x42, 0x47, 0x80, 0x4f, 0x31, 0xda, 0x5d, 0x58, 0xb1, 0xdb, 0x54,
  0x33, 0xcc, 0xc7, 0x49, 0x07, 0xa1, 0x00, 0x98, 0x4e, 0x9c, 0xe3, 0xc8,
  0xc4, 0x5e, 0xde, 0x45, 0xd6, 0xcf, 0x04, 0xe8, 0x7d, 0xa5, 0xab, 0x3a,
  0xd4, 0x8e, 0x5f, 0xdb, 0xb3, 0x3f, 0xf9, 0x3b, 0x73, 0x32, 0x0a, 0xcc,
  0x2d, 0xcc, 0x17, 0xf8, 0x88, 0x9e, 0x2c, 0x76, 0xba, 0x10, 0x85, 0x0c,
  0xaa, 0xd3, 0x65, 0x3b, 0x91, 0x10, 0xd4, 0xe3, 0xed, 0x88, 0x15, 0xea,
  0x9b, 0x25, 0x82, 0x2d, 0x56, 0x2f, 0x75, 0xc2, 0xf2, 0xaf, 0xdd, 0x24,
  0xd5, 0x3e, 0x3c, 0x95, 0x76, 0x88, 0x84, 0x0f, 0x0d, 0xd1, 0xb5, 0x5c,
  0x3e, 0xae, 0xf7, 0xb6, 0x49, 0x5c, 0x2c, 0xf2, 0xba, 0xe9, 0xab, 0x4f,
  0x37, 0x64, 0x9b, 0x30, 0x18, 0xaa, 0x54, 0x40, 0x04, 0xea, 0x3d, 0x25,
  0x4d, 0x02, 0x29, 0x71, 0x6f, 0x4d, 0x82, 0x9b, 0xc3, 0x44, 0x2a, 0x9d,
  0x0c, 0x98, 0xd3, 0xc8, 0x15, 0x0d, 0x04, 0x93, 0x60, 0x30, 0xc7, 0x5e,
  0x79, 0xea, 0x53, 0x9d, 0xc0, 0x0e, 0x81, 0xac, 0x90, 0xbc, 0x9e, 0x1e,
  0xd2, 0x28, 0x0f, 0x10, 0xf5, 0x1f, 0xdf, 0x38, 0x7f, 0x8a, 0x90, 0x8d,
  0x49, 0x07, 0x7d, 0x78, 0xcb, 0xa7, 0xef, 0x92, 0x6d, 0x3b, 0x13, 0x95,
  0x9b, 0xba, 0x83, 0xc6, 0xb3, 0x71, 0x25, 0x27, 0x07, 0x99, 0x54, 0x82,
  0x3d, 0xec, 0xc5, 0xf8, 0xb4, 0xa0, 0x38, 0x7a, 0x59, 0x6a, 0x0b, 0xca,
  0x69, 0x6c, 0x17, 0xa4, 0x18, 0xe0, 0xb4, 0xaa, 0x89, 0x99, 0x8f, 0xcb,
  0x71, 0x34, 0x09, 0x1b, 0x6e, 0xe6, 0x87, 0x00, 0xb5, 0xba, 0x70, 0x8a,
  0x29, 0x3d, 0x9a, 0x06, 0x18, 0x2d, 0x66, 0x5e, 0x61, 0x37, 0xeb, 0xdd,
  0x5e, 0xc8, 0x28, 0x92, 0x05, 0x30, 0xfd, 0xb8, 0x65, 0xb1, 0x7f, 0xbf,
  0x2d, 0x55, 0x12, 0x91, 0xc1, 0x02, 0x81, 0x81, 0x00, 0xda, 0x65, 0xda,
  0x38, 0x7c, 0x18, 0xfb, 0x00, 0x11, 0x60, 0xeb, 0x37, 0x65, 0xb8, 0x83,
  0x62, 0x88, 0xc4, 0x3a, 0x4e, 0x64, 0x6a, 0xf3, 0x3e, 0x4e, 0xc0, 0x34,
  0x19, 0x8a, 0xcb, 0x4a, 0xca, 0x2f, 0x5d, 0x50, 0x7a, 0xac, 0xf7, 0x9e,
  0x87, 0x5a, 0xfc, 0x4d, 0x49, 0xd7, 0xf9, 0x21, 0xf5, 0x0b, 0x6f, 0x57,
  0x41, 0x3d, 0x8f, 0xb8, 0xec, 0x7f, 0xcc, 0x92, 0x09, 0xbe, 0xd3, 0xa4,
  0xc3, 0x14, 0x85, 0x21, 0x5d, 0x05, 0xa3, 0xaa, 0x20, 0xf6, 0x62, 0x44,
  0x50, 0x03, 0x5e, 0x53, 0x4a, 0xcd, 0x6a, 0xb6, 0x65, 0x8e, 0x4e, 0x4b,
  0x3f, 0x25, 0xc6, 0x16, 0x31, 0xf5, 0x99, 0x13, 0x77, 0x42, 0xda, 0xdc,
  0x70, 0x4d, 0x65, 0xb0, 0x99, 0x0f, 0xdf, 0x5a, 0xb1, 0x45, 0xf0, 0xb9,
  0x8e, 0xa0, 0xae, 0x4f, 0x4d, 0x65, 0x09, 0x84, 0xb5, 0x38, 0x29, 0xbf,
  0x69, 0xe0, 0x88, 0x1f, 0x27, 0x02, 0x81, 0x81, 0x00, 0xd3, 0x2a, 0x59,
  0xec, 0x28, 0xc3, 0x0d, 0x4f, 0x92, 0x96, 0xca, 0x67, 0x94, 0xfc, 0x2e,
  0xa6, 0x86, 0x68, 0x45, 0x53, 0x92, 0xcc, 0x86, 0x7f, 0x8a, 0xe1, 0x5d,
  0xe8, 0x1d, 0x9e, 0xbb, 0x1e, 0x00, 0x26, 0x1d, 0x80, 0x12, 0xff, 0x9c,
  0x11, 0x0a, 0xbd, 0xa6, 0xc3, 0x8d, 0x48, 0xda, 0xfc, 0x10, 0xf7, 0x7a,
  0x16, 0x07, 0x15, 0xa0, 0x3a, 0xd3, 0x94, 0xfb, 0x52, 0x87, 0x39, 0xee,
  0xe7, 0xc4, 0x26, 0x49, 0x16, 0xc6, 0xc0, 0x83, 0x25, 0xbf, 0x6a, 0x4e,
  0x8c, 0x0b, 0x10, 0x85, 0x66, 0xab, 0x7e, 0xae, 0xac, 0x4c, 0x69, 0x3c,
  0x44, 0xeb, 0xcd, 0xe9, 0xf6, 0x64, 0x8b, 0x4a, 0xd8, 0x6a, 0x4d, 0x6d,
  0x47, 0xa9, 0xb8, 0x55, 0x72, 0xc1, 0xfd, 0xf4, 0x81, 0x4c, 0x66, 0xbe,
  0x49, 0xf2, 0x75, 0x4f, 0x80, 0xf1, 0x20, 0x38, 0xb8, 0x6a, 0x1b, 0x75,
  0x41, 0x30, 0x0f, 0x1b, 0x3f, 0x02, 0x81, 0x80, 0x09, 0x35, 0xfa, 0x7a,
  0x1f, 0x61, 0xbe, 0x54, 0x46, 0x67, 0x5c, 0x04, 0x3e, 0x1a, 0x06, 0x10,
  0x85, 0xcc, 0x20, 0xd9, 0x65, 0x8a, 0xcd, 0x2f, 0x77, 0x8a, 0xcb, 0xa7,
  0xb8, 0x1e, 0xd2, 0xcc, 0xac, 0x2a, 0xb7, 0x56, 0x35, 0x2d, 0x4c, 0x56,
  0x51, 0x14, 0x0a, 0xfe, 0x6e, 0x49, 0x67, 0x91, 0x3a, 0x26, 0x3b, 0xfb,
  0xd8, 0x68, 0xd3, 0x57, 0xc6, 0x1c, 0x0e, 0x9c, 0xb2, 0x9b, 0xa2, 0x7b,
  0x47, 0xc6, 0x45, 0x9d, 0xf2, 0xba, 0xf0, 0x55, 0xeb, 0x8e, 0x41, 0x6b,
  0x4e, 0x79, 0x0f, 0xf2, 0x3b, 0xaf, 0xa0, 0x79, 0xb0, 0x02, 0xc5, 0x51,
  0xa8, 0x7a, 0x2e, 0x3d, 0x75, 0x2a, 0x3b, 0x93, 0xf0, 0x11, 0xe2, 0xf2,
  0x29, 0x91, 0x7c, 0x5d, 0x38, 0x3a, 0x27, 0x4d, 0x0a, 0xb2, 0x18, 0x61,
  0x57, 0x8d, 0x82, 0x72, 0xb5, 0x2c, 0x2d, 0x98, 0xa7, 0x01, 0xbb, 0xbc,
  0xef, 0x67, 0x4e, 0x49, 0x02, 0x81, 0x81, 0x00, 0xb2, 0x70, 0x53, 0x54,
  0x70, 0x8d, 0x82, 0xad, 0xff, 0x1d, 0x55, 0x24, 0x7a, 0x8d, 0x2f, 0x8e,
  0xa0, 0x7d, 0x74, 0x37, 0xcf, 0x10, 0xed, 0x86, 0xd1, 0x80, 0xe7, 0xad,
  0xc1, 0x79, 0xe4, 0x7c, 0xd1, 0x7b, 0x63, 0xea, 0x5a, 0x23, 0x8d, 0x6a,
  0x09, 0x3d, 0x81, 0xb2, 0x35, 0xad, 0x9e, 0xfe, 0xea, 0x07, 0x76, 0x2f,
  0x2f, 0x05, 0x63, 0x44, 0xd2, 0x8e, 0x4e, 0x61, 0xca, 0xcb, 0x75, 0xca,
  0x7b, 0xc2, 0x2e, 0x79, 0x04, 0xb2, 0xa1, 0x20, 0x40, 0xc4, 0x40, 0x63,
  0xae, 0xe5, 0xe3, 0x14, 0x83, 0x4e, 0xa5, 0xa4, 0x0b, 0x5d, 0xd2, 0x04,
  0x1b, 0x8f, 0x01, 0x69, 0xa8, 0x44, 0xdc, 0x96, 0x4c, 0x1d, 0xe9, 0x7e,
  0x69, 0x38, 0xcf, 0x5c, 0x0d, 0xf9, 0xdf, 0xa7, 0x73, 0x3c, 0x4f, 0x08,
  0x85, 0xce, 0x03, 0xc4, 0xdd, 0xfd, 0x70, 0x70, 0xc5, 0x99, 0x36, 0x58,
  0x43, 0x98, 0x40, 0x59, 0x02, 0x81, 0x81, 0x00, 0xd5, 0xaa, 0xfb, 0xec,
  0x8d, 0xc6, 0xdd, 0xfa, 0x2b, 0x5a, 0x24, 0xd0, 0xda, 0x58, 0xbd, 0x87,
  0x92, 0x1a, 0x29, 0x62, 0x13, 0x1d, 0x4b, 0x79, 0x1b, 0xbe, 0x79, 0x7d,
  0xad, 0x79, 0xca, 0x17, 0x75, 0xda, 0xe8, 0x32, 0xe8, 0xa0, 0x9e, 0xa8,
  0x77, 0x53, 0xac, 0x38, 0xd6, 0xeb, 0xe6, 0x22, 0x65, 0xc4, 0xaa, 0x4c,
  0xc8, 0xd0, 0x33, 0x1a, 0x1e, 0xbe, 0xbd, 0x73, 0x09, 0x4a, 0xfa, 0x85,
  0x5c, 0xf3, 0x0c, 0x9c, 0x81, 0x56, 0x30, 0xa7, 0xf7, 0x9b, 0xf4, 0x92,
  0x9c, 0x6b, 0x93, 0x6a, 0x00, 0x33, 0xdc, 0x2f, 0x54, 0x1e, 0x78, 0xd4,
  0x97, 0xec, 0x24, 0xa2, 0xdb, 0x3d, 0x03, 0x33, 0x09, 0xb2, 0x2c, 0x03,
  0x05, 0x40, 0xde, 0x52, 0xf2, 0x9b, 0xfa, 0x00, 0x8d, 0x4b, 0xfe, 0x5b,
  0x9b, 0x9c, 0x73, 0xad, 0xfb, 0x7a, 0x00, 0x42, 0x62, 0x9e, 0xa0, 0x95,
  0x55, 0x50, 0x32, 0x87
};
static unsigned int enc_priv_key_len = 1192;

const struct bootutil_key bootutil_enc_key = {
    .key = enc_priv_key,
    .len = &enc_priv_key_len,
};
#elif defined(MCUBOOT_ENCRYPT_EC256)
extern const unsigned char enc_priv_key[];
extern unsigned int enc_priv_key_len;
const struct bootutil_key bootutil_enc_key = {
    .key = enc_priv_key,
    .len = &enc_priv_key_len,
};
#elif defined(MCUBOOT_ENCRYPT_X25519)
unsigned char enc_key[] = {
  0x30, 0x2e, 0x02, 0x01, 0x00, 0x30, 0x05, 0x06, 0x03, 0x2b, 0x65, 0x6e,
  0x04, 0x22, 0x04, 0x20, 0x28, 0x80, 0x2f, 0xef, 0xef, 0x82, 0x95, 0x50,
  0xf1, 0x41, 0x93, 0x03, 0x6c, 0x1b, 0xb9, 0x49, 0x6c, 0x51, 0xe5, 0x26,
  0x87, 0x8f, 0x77, 0x07, 0xf8, 0xb4, 0x1f, 0x04, 0x45, 0x6d, 0x84, 0x4f,
};
static unsigned int enc_key_len = 48;
const struct bootutil_key bootutil_enc_key = {
    .key = enc_key,
    .len = &enc_key_len,
};
#elif defined(MCUBOOT_ENCRYPT_KW)
#error "Encrypted images with AES-KW is not implemented yet."
#endif
