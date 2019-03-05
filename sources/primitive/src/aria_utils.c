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
#include "aria_debug.h"
#include "aria_test.h"
#include "aria_type.h"

/* convert Hexa Ascii character to hexa value */
/* example: 'f' => 0xf */
char atoh(const char C) {
  /* for ABCEDF characters */
  if ((0x41 <= C) && (C <= 0x46)) return (C - 0x37);
  /* for abcdef characters */
  else if ((0x61 <= C) && (C <= 0x66))
    return (C - 0x57);
  /* for 01123456789 characters */
  else if ((0x30 <= C) && (C <= 0x39))
    return (C - 0x30);
  /* not an hexa character */
  else
    return -1;
}

/* fill remaining spaces in buffer with value 0 */
unsigned char* fillBuffer(unsigned char* buffer,
                          unsigned int   start,
                          unsigned int   end) {
  for (int i = start; i < end; i++) {
    buffer[i] = 0;
  }
  return buffer;
}

/* print data inside buffer. just for debug */
void printBuffer(unsigned char* buffer, unsigned int length) {
  printf("Buffer Data: ");
  for (int i = 0; i < length; i++) {
    printf("0x%x ", buffer[i]);
  }
  printf("\n");
}

/* compare values between two arrays */
int compareBuffer(unsigned char* buffer1,
                  unsigned char* buffer2,
                  unsigned int   length) {
  /* NOT IMPLEMENTED */
  return 0;
}
