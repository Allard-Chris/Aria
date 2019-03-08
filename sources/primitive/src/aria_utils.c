/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria utils functions
**********************************************/
#include "aria_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* convert Hexa Ascii character to hexa value */
/* example: 'f' => 0xf */
char atoh(const char C) {
  char i;
  /* for ABCEDF characters */
  if ((0x41 <= C) && (C <= 0x46)) i = C - 0x37;
  /* for abcdef characters */
  else if ((0x61 <= C) && (C <= 0x66))
    i = C - 0x57;
  /* for 01123456789 characters */
  else if ((0x30 <= C) && (C <= 0x39))
    i = C - 0x30;
  /* not an hexa character */
  else
    i = -1;
  return i;
}

/* fill remaining spaces in u8 buffer with value 0 */
void fillBuffer(u8* buffer, const unsigned int start, const unsigned int end) {
  for (int i = start; i < end; i++) {
    buffer[i] = 0;
  }
}

/* print data inside buffer. just for debug */
void printBuffer(u8* buffer, unsigned int length) {
  fprintf(stdout, "Buffer Data: ");
  for (unsigned int i = 0; i < length; i++) {
    fprintf(stdout, "0x%hhx ", buffer[i]);
  }
  fprintf(stdout, "\n");
}

/* convert array of 16 * u8 into 2 u64 array */
void u8ArrayToU64(const u8* input, u64* low_bytes, u64* high_bytes) {
  for (unsigned int i = CHUNK_16_OCTETS - 1; i >= (CHUNK_16_OCTETS / 2); i--) {
    *high_bytes <<= 8;
    *high_bytes += (u8)input[i];
    *low_bytes <<= 8;
    *low_bytes += (u8)input[i - (CHUNK_16_OCTETS / 2)];
  }
}

/* convert 2 array of u64 into array of 16 * 8 */
void u64ToU8Array(u8* output, const u64* low_bytes, const u64* high_bytes) {
  u64 tmp_low_bytes = *low_bytes;
  u64 tmp_high_bytes = *high_bytes;
  for (unsigned int i = 0; i < (CHUNK_16_OCTETS / 2); i++) {
    output[i] = (u8)tmp_low_bytes;
    tmp_low_bytes >>= 8;
    output[i + (CHUNK_16_OCTETS / 2)] = (u8)tmp_high_bytes;
    tmp_high_bytes >>= 8;
  }
}