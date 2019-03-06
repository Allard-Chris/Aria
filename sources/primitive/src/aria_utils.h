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

/* fill remaining spaces in array with value 0 */
void fillArray(u8 array[], const unsigned int start, const unsigned int end);

/* print data inside buffer. just for debug */
void printBuffer(unsigned char* buffer, unsigned int length);

/* compare values between two arrays */
int compareBuffer(unsigned char* buffer1,
                  unsigned char* buffer2,
                  unsigned int   length);

/* convert array of 16 * u8 into 2 u64 array */
void u8ArrayToU64(unsigned char* input, u64* low_bytes, u64* high_bytes);

/* convert 2 array of u64 into array of 16 * 8 */
void u64ToU8Array(unsigned char* output, u64* low_bytes, u64* high_bytes);

#endif