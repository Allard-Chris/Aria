/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria tests constants
**********************************************/

#include "aria_type.h"

/* Tips: to avoid very long const name: */
/* E = ENCRYPT */
/* 128 = key size */
/* R1 = round 1 */
/* KA = Key_add, SL = substition layer, DL = diffusion_layer */

/* Values from Aria specification tests for 128-bit key in encryption */
const u8 E128_R1_KA[CHUNK_SIZE_OCTET] = {0xd4, 0x04, 0x85, 0x6f, 0x3d, 0x1e,
                                         0xe3, 0xb2, 0x68, 0x4b, 0x0a, 0x08,
                                         0x07, 0xa4, 0xd5, 0x09};

const u8 E128_R1_SL[CHUNK_SIZE_OCTET] = {0x48, 0x94, 0x67, 0xd9, 0x27, 0x59,
                                         0x4d, 0xd5, 0x45, 0x95, 0xa3, 0x50,
                                         0xc5, 0xa9, 0xb5, 0x39};

const u8 E128_R1_DL[CHUNK_SIZE_OCTET] = {0x7f, 0xc7, 0xf1, 0x2b, 0xef, 0xd0,
                                         0xa0, 0x79, 0x1d, 0xe8, 0x7f, 0xa9,
                                         0x6b, 0x46, 0x9f, 0x52};

const u8 E128_R2_KA[CHUNK_SIZE_OCTET] = {0x49, 0x5b, 0x94, 0xcf, 0x5e, 0xc7,
                                         0xd7, 0xd2, 0x6c, 0xd2, 0x41, 0xb7,
                                         0x0d, 0x47, 0x27, 0xa6};

const u8 E128_R2_SL[CHUNK_SIZE_OCTET] = {0xa4, 0xe2, 0x22, 0xda, 0x9d, 0x5b,
                                         0x0e, 0xa2, 0xb8, 0xc9, 0x83, 0x34,
                                         0xf3, 0x58, 0xcc, 0xd4};

const u8 E128_R2_DL[CHUNK_SIZE_OCTET] = {0xac, 0x8d, 0xe1, 0x7e, 0x49, 0xf7,
                                         0xc5, 0x11, 0x76, 0x18, 0x99, 0x31,
                                         0x62, 0xb1, 0x89, 0xe9};

const u8 E128_R3_KA[CHUNK_SIZE_OCTET] = {0xaf, 0xe5, 0x35, 0x8f, 0x74, 0xe3,
                                         0x8c, 0x6a, 0x13, 0x31, 0x34, 0x4b,
                                         0xaa, 0xb8, 0x6e, 0x39};

const u8 E128_R3_SL[CHUNK_SIZE_OCTET] = {0x79, 0x5a, 0xd9, 0x9a, 0x92, 0x33,
                                         0xf0, 0x0a, 0x7d, 0x73, 0x28, 0xc3,
                                         0xac, 0x70, 0x45, 0xaa};

const u8 E128_R3_DL[CHUNK_SIZE_OCTET] = {0xc3, 0xe8, 0xd5, 0x9e, 0xc2, 0xe6,
                                         0x2d, 0x52, 0x49, 0xca, 0x27, 0x41,
                                         0x65, 0x3c, 0xb7, 0xdd};

const u8 E128_R4_KA[CHUNK_SIZE_OCTET] = {0x05, 0xac, 0x80, 0xb5, 0x96, 0x7c,
                                         0x0b, 0x6d, 0xf1, 0x1a, 0x92, 0x48,
                                         0x63, 0x1e, 0x29, 0x31};

const u8 E128_R4_SL[CHUNK_SIZE_OCTET] = {0x36, 0x44, 0xcd, 0xf2, 0x35, 0xee,
                                         0x2b, 0xca, 0x2b, 0xfb, 0x4f, 0x8d,
                                         0x00, 0xc4, 0xa5, 0x73};

const u8 E128_R4_DL[CHUNK_SIZE_OCTET] = {0x5d, 0x4a, 0xeb, 0xb1, 0x65, 0xe1,
                                         0x41, 0xff, 0x75, 0x9f, 0x66, 0x9e,
                                         0x1e, 0x85, 0xcc, 0x45};

const u8 E128_R5_KA[CHUNK_SIZE_OCTET] = {0x02, 0xd6, 0xa8, 0xf8, 0x34, 0x13,
                                         0x93, 0x10, 0x41, 0xb8, 0xe1, 0x2f,
                                         0xb9, 0x04, 0xb5, 0x09};

const u8 E128_R5_SL[CHUNK_SIZE_OCTET] = {0x77, 0x1c, 0x6f, 0xf7, 0x18, 0xcb,
                                         0x22, 0x3e, 0x83, 0x70, 0xe0, 0x4d,
                                         0x56, 0x94, 0xd2, 0x39};

const u8 E128_R5_DL[CHUNK_SIZE_OCTET] = {0x78, 0x06, 0xe4, 0x69, 0xf6, 0x88,
                                         0x74, 0xc5, 0x00, 0x4b, 0x5f, 0x4a,
                                         0x04, 0x6b, 0xbc, 0xfa};

const u8 E128_R6_KA[CHUNK_SIZE_OCTET] = {0xd7, 0xec, 0xc8, 0x65, 0x11, 0x95,
                                         0xc2, 0x1b, 0x42, 0xef, 0x2b, 0x2b,
                                         0xf0, 0x59, 0x80, 0xae};

const u8 E128_R6_SL[CHUNK_SIZE_OCTET] = {0x0d, 0x80, 0xe8, 0x21, 0xe3, 0x4b,
                                         0x25, 0x03, 0xf6, 0xd3, 0xf1, 0xae,
                                         0x17, 0x1e, 0xcd, 0x9d};

const u8 E128_R6_DL[CHUNK_SIZE_OCTET] = {0x11, 0x0f, 0x93, 0xc9, 0xa6, 0x30,
                                         0xcd, 0xd5, 0x1f, 0x97, 0xd2, 0x20,
                                         0x24, 0x13, 0x34, 0x5a};

const u8 E128_R7_KA[CHUNK_SIZE_OCTET] = {0x23, 0x4d, 0x15, 0x12, 0xe2, 0x8a,
                                         0x80, 0x63, 0xdb, 0xdd, 0x11, 0x26,
                                         0xd6, 0xbb, 0x7f, 0x76};

const u8 E128_R7_SL[CHUNK_SIZE_OCTET] = {0x26, 0x2f, 0x2f, 0x5e, 0x98, 0xf1,
                                         0x3a, 0x2c, 0xb9, 0x44, 0xe3, 0x77,
                                         0xf6, 0x8a, 0x6b, 0xad};

const u8 E128_R7_DL[CHUNK_SIZE_OCTET] = {0xe0, 0x54, 0x42, 0x8e, 0xf0, 0x88,
                                         0xfe, 0xf9, 0x79, 0x28, 0x24, 0x1c,
                                         0xd3, 0xbe, 0x49, 0x9e};

const u8 E128_R8_KA[CHUNK_SIZE_OCTET] = {0x9f, 0xcb, 0xeb, 0xbb, 0x84, 0x50,
                                         0xbc, 0x40, 0x69, 0x32, 0x7c, 0x1a,
                                         0xe4, 0xcf, 0xa2, 0xe};

const u8 E128_R8_SL[CHUNK_SIZE_OCTET] = {0x6e, 0x13, 0xe9, 0x8a, 0x4f, 0x8c,
                                         0x65, 0x2d, 0xe4, 0x6c, 0x10, 0x2e,
                                         0xae, 0x45, 0x3a, 0x5a};

const u8 E128_R8_DL[CHUNK_SIZE_OCTET] = {0x57, 0x34, 0xf3, 0x8e, 0xa1, 0xca,
                                         0x3d, 0xdd, 0x10, 0x2e, 0x71, 0xf9,
                                         0x5e, 0x1d, 0x5f, 0x97};

const u8 E128_R9_KA[CHUNK_SIZE_OCTET] = {0xfd, 0x8d, 0x36, 0xf9, 0x90, 0x36,
                                         0xef, 0xce, 0xbd, 0x78, 0x06, 0xbc,
                                         0xd1, 0xd2, 0xb9, 0x43};

const u8 E128_R9_SL[CHUNK_SIZE_OCTET] = {0x54, 0x1f, 0x24, 0x4c, 0x60, 0x85,
                                         0x61, 0x4e, 0x7a, 0x07, 0xa5, 0x18,
                                         0x3e, 0xa2, 0xdb, 0xaf};

const u8 E128_R9_DL[CHUNK_SIZE_OCTET] = {0x49, 0x03, 0x32, 0x5b, 0xe3, 0xe5,
                                         0x00, 0xcc, 0xcd, 0x52, 0xfb, 0xa4,
                                         0x35, 0x4a, 0x39, 0xae};

const u8 E128_R10_KA[CHUNK_SIZE_OCTET] = {0x66, 0x47, 0x11, 0xe0, 0xe5, 0xa3,
                                          0x5a, 0x76, 0x17, 0x04, 0x6f, 0x05,
                                          0xab, 0xf2, 0xbd, 0xf7};

const u8 E128_R10_SL[CHUNK_SIZE_OCTET] = {0xd3, 0x58, 0x82, 0x90, 0x2a, 0xba,
                                          0xbe, 0x42, 0x87, 0x87, 0xa8, 0xc2,
                                          0x0e, 0xb5, 0x7a, 0xf8};

const u8 E128_R10_DL[CHUNK_SIZE_OCTET] = {0xcb, 0x8c, 0x50, 0x8e, 0x2c, 0x4f,
                                          0x87, 0x88, 0x06, 0x39, 0xdc, 0x89,
                                          0x6d, 0x25, 0xec, 0x9d};

const u8 E128_R11_KA[CHUNK_SIZE_OCTET] = {0x54, 0x0b, 0x22, 0x0e, 0xa3, 0x12,
                                          0xdf, 0x85, 0x87, 0x37, 0x24, 0x54,
                                          0xc1, 0x36, 0x47, 0x76};

const u8 E128_R11_SL[CHUNK_SIZE_OCTET] = {0x20, 0x46, 0x94, 0x62, 0x0a, 0x64,
                                          0xef, 0x36, 0x17, 0xe4, 0xa6, 0x02,
                                          0x78, 0x85, 0x16, 0xad};

const u8 E128_R11_DL[CHUNK_SIZE_OCTET] = {0xe7, 0xe0, 0xd2, 0x45, 0x7e, 0xd7,
                                          0x3d, 0x23, 0xd4, 0x81, 0x42, 0x40,
                                          0x95, 0xaf, 0xdc, 0xa0};

const u8 E128_R12_KA[CHUNK_SIZE_OCTET] = {0x61, 0x64, 0x46, 0x2f, 0x6b, 0x8c,
                                          0xda, 0x5d, 0x2c, 0x91, 0x36, 0x08,
                                          0xd2, 0x4c, 0x83, 0x0d};

const u8 E128_R12_SL[CHUNK_SIZE_OCTET] = {0xd8, 0x12, 0x5a, 0xbb, 0x05, 0x82,
                                          0x57, 0xa4, 0x42, 0x47, 0x05, 0x62,
                                          0x7f, 0x35, 0xec, 0x4d};

const u8 E128_R12_DL[CHUNK_SIZE_OCTET] = {0xd7, 0x18, 0xfb, 0xd6, 0xab, 0x64,
                                          0x4c, 0x73, 0x9d, 0xa9, 0x5f, 0x3b,
                                          0xe6, 0x45, 0x17, 0x78};

/* Values from Aria specification tests for 128-bit key in decryption */

const u8 D128_R1_KA[CHUNK_SIZE_OCTET] = {0xd8, 0x12, 0x5a, 0xbb, 0x05, 0x82,
                                         0x57, 0xa4, 0x42, 0x47, 0x05, 0x62,
                                         0x7f, 0x35, 0xec, 0x4d};

const u8 D128_R1_SL[CHUNK_SIZE_OCTET] = {0x61, 0x64, 0x46, 0x2f, 0x6b, 0x8c,
                                         0xda, 0x5d, 0x2c, 0x91, 0x36, 0x08,
                                         0xd2, 0x4c, 0x83, 0x0d};

const u8 D128_R1_DL[CHUNK_SIZE_OCTET] = {0xec, 0xf5, 0x34, 0x41, 0x01, 0x09,
                                         0x43, 0x2b, 0x44, 0x0a, 0x52, 0x9f,
                                         0xee, 0x9f, 0xb3, 0xd2};

const u8 D128_R2_KA[CHUNK_SIZE_OCTET] = {0x20, 0x46, 0x94, 0x62, 0x0a, 0x64,
                                         0xef, 0x36, 0x17, 0xe4, 0xa6, 0x02,
                                         0x78, 0x85, 0x16, 0xad};

const u8 D128_R2_SL[CHUNK_SIZE_OCTET] = {0x54, 0x0b, 0x22, 0x0e, 0xa3, 0x12,
                                         0xdf, 0x85, 0x87, 0x37, 0x24, 0x54,
                                         0xc1, 0x36, 0x47, 0x76};

const u8 D128_R2_DL[CHUNK_SIZE_OCTET] = {0xb3, 0xb2, 0xb0, 0xc2, 0x86, 0x84,
                                         0x17, 0xfe, 0x1d, 0x40, 0x26, 0xbb,
                                         0xd1, 0x95, 0xcf, 0x4d};

const u8 D128_R3_KA[CHUNK_SIZE_OCTET] = {0xd3, 0x58, 0x82, 0x90, 0x2a, 0xba,
                                         0xbe, 0x42, 0x87, 0x87, 0xa8, 0xc2,
                                         0x0e, 0xb5, 0x7a, 0xf8};

const u8 D128_R3_SL[CHUNK_SIZE_OCTET] = {0x66, 0x47, 0x11, 0xe0, 0xe5, 0xa3,
                                         0x5a, 0x76, 0x17, 0x04, 0x6f, 0x05,
                                         0xab, 0xf2, 0xbd, 0xf7};

const u8 D128_R3_DL[CHUNK_SIZE_OCTET] = {0x03, 0x8b, 0xce, 0x96, 0x8c, 0x63,
                                         0x33, 0xb6, 0xd8, 0xcb, 0x1a, 0x70,
                                         0xd0, 0x20, 0x7c, 0x9f};

const u8 D128_R4_KA[CHUNK_SIZE_OCTET] = {0x54, 0x1f, 0x24, 0x4c, 0x60, 0x85,
                                         0x61, 0x4e, 0x7a, 0x07, 0xa5, 0x18,
                                         0x3e, 0xa2, 0xdb, 0xaf};

const u8 D128_R4_SL[CHUNK_SIZE_OCTET] = {0xfd, 0x8d, 0x36, 0xf9, 0x90, 0x36,
                                         0xef, 0xce, 0xbd, 0x78, 0x06, 0xbc,
                                         0xd1, 0xd2, 0xb9, 0x43};

const u8 D128_R4_DL[CHUNK_SIZE_OCTET] = {0x28, 0x99, 0xda, 0xd4, 0x06, 0x60,
                                         0x78, 0x99, 0xb9, 0x7d, 0x3a, 0x81,
                                         0x8f, 0x4c, 0xdf, 0xe5};

const u8 D128_R5_KA[CHUNK_SIZE_OCTET] = {0x6e, 0x13, 0xe9, 0x8a, 0x4f, 0x8c,
                                         0x65, 0x2d, 0xe4, 0x6c, 0x10, 0x2e,
                                         0xae, 0x45, 0x3a, 0x5a};

const u8 D128_R5_SL[CHUNK_SIZE_OCTET] = {0x9f, 0xcb, 0xeb, 0xbb, 0x84, 0x50,
                                         0xbc, 0x40, 0x69, 0x32, 0x7c, 0x1a,
                                         0xe4, 0xcf, 0xa2, 0xe5};

const u8 D128_R5_DL[CHUNK_SIZE_OCTET] = {0xb5, 0xa1, 0x94, 0x84, 0x10, 0xfd,
                                         0x51, 0x94, 0xc6, 0xe4, 0xff, 0xe0,
                                         0x10, 0x02, 0x7a, 0x04};

const u8 D128_R6_KA[CHUNK_SIZE_OCTET] = {0x26, 0x2f, 0x2f, 0x5e, 0x98, 0xf1,
                                         0x3a, 0x2c, 0xb9, 0x44, 0xe3, 0x77,
                                         0xf6, 0x8a, 0x6b, 0xad};

const u8 D128_R6_SL[CHUNK_SIZE_OCTET] = {0x23, 0x4d, 0x15, 0x12, 0xe2, 0x8a,
                                         0x80, 0x63, 0xdb, 0xdd, 0x11, 0x26,
                                         0xd6, 0xbb, 0x7f, 0x76};

const u8 D128_R6_DL[CHUNK_SIZE_OCTET] = {0xb2, 0x5a, 0xb8, 0x39, 0x48, 0x78,
                                         0xf4, 0x4f, 0x33, 0xeb, 0x1b, 0xf2,
                                         0x96, 0xa3, 0xdd, 0x8c};

const u8 D128_R7_KA[CHUNK_SIZE_OCTET] = {0x0d, 0x80, 0xe8, 0x21, 0xe3, 0x4b,
                                         0x25, 0x03, 0xf6, 0xd3, 0xf1, 0xae,
                                         0x17, 0x1e, 0xcd, 0x9d};

const u8 D128_R7_SL[CHUNK_SIZE_OCTET] = {0xd7, 0xec, 0xc8, 0x65, 0x11, 0x95,
                                         0xc2, 0x1b, 0x42, 0xef, 0x2b, 0x2b,
                                         0xf0, 0x59, 0x80, 0xae};

const u8 D128_R7_DL[CHUNK_SIZE_OCTET] = {0xc2, 0xb5, 0x61, 0x80, 0xcd, 0x72,
                                         0x69, 0x8b, 0xed, 0x37, 0x4f, 0x38,
                                         0xc9, 0x5b, 0x72, 0x67};

const u8 D128_R8_KA[CHUNK_SIZE_OCTET] = {0x77, 0x1c, 0x6f, 0xf7, 0x18, 0xcb,
                                         0x22, 0x3e, 0x83, 0x70, 0xe0, 0x4d,
                                         0x56, 0x94, 0xd2, 0x39};

const u8 D128_R8_SL[CHUNK_SIZE_OCTET] = {0x02, 0xd6, 0xa8, 0xf8, 0x34, 0x13,
                                         0x93, 0x10, 0x41, 0xb8, 0xe1, 0x2f,
                                         0xb9, 0x04, 0xb5, 0x09};

const u8 D128_R8_DL[CHUNK_SIZE_OCTET] = {0x17, 0xe2, 0x0f, 0x7e, 0x6b, 0xff,
                                         0x5e, 0x6e, 0x1c, 0x77, 0x9c, 0xc0,
                                         0xd3, 0xdd, 0xff, 0xf0};

const u8 D128_R9_K[CHUNK_SIZE_OCTET] = {};

const u8 D128_R9_B[CHUNK_SIZE_OCTET] = {};

const u8 D128_R9_D[CHUNK_SIZE_OCTET] = {};

const u8 D128_R10_S[CHUNK_SIZE_OCTET] = {};

const u8 D128_R10_K[CHUNK_SIZE_OCTET] = {};

const u8 D128_R10_B[CHUNK_SIZE_OCTET] = {};

const u8 D128_R10_D[CHUNK_SIZE_OCTET] = {};

const u8 D128_R11_S[CHUNK_SIZE_OCTET] = {};

const u8 D128_R11_K[CHUNK_SIZE_OCTET] = {};

const u8 D128_R11_B[CHUNK_SIZE_OCTET] = {};

const u8 D128_R11_D[CHUNK_SIZE_OCTET] = {};

const u8 D128_R12_S[CHUNK_SIZE_OCTET] = {};

const u8 D128_R12_K[CHUNK_SIZE_OCTET] = {};

const u8 D128_R12_B[CHUNK_SIZE_OCTET] = {};

const u8 D128_R12_D[CHUNK_SIZE_OCTET] = {};