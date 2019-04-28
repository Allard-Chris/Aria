/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria primitive
**********************************************/

#ifndef HEADER_ARIA_LOCL_H
#define HEADER_ARIA_LOCL_H

#include <openssl/opensslconf.h>

#ifdef OPENSSL_NO_ARIA
#error ARIA is disabled.
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

#endif /* !HEADER_ARIA_LOCL_H */
