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

/* convert Hexa Ascii character to hexa value */
char atoh(const char C);

/* fill remaining spaces in buffer with value 0 */
unsigned char* fillBuffer(unsigned char* buffer, unsigned int length);

/* print data inside buffer. just for debug */
void printBuffer(unsigned char* buffer, unsigned int length);

/* compare values between two arrays */
int compareBuffer(unsigned char* buffer1,
                  unsigned char* buffer2,
                  unsigned int   length);

#endif