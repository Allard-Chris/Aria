/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria utils functions
**********************************************/
#ifndef ARIA_UTILS
#define ARIA_UTILS
#include "aria_debug.h"
#include "aria_type.h"

/* convert Hexa Ascii character to hexa value */
char atoh(const char C);

/* fill remaining spaces in buffer with value 0 */
void fillBuffer(u8* buffer, const unsigned int start, const unsigned int end);

/* print data inside buffer. just for debug */
void printBuffer(unsigned char* buffer, unsigned int length);

/* convert array of 16 * u8 into 2 u64 array */
void u8ArrayToU64(const u8* input, u64* low_bytes, u64* high_bytes);

/* convert 2 array of u64 into array of 16 * 8 */
void u64ToU8Array(u8* output, const u64* low_bytes, const u64* high_bytes);

#endif /* ARIA_UTILS */