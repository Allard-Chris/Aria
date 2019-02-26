/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria utils functions
**********************************************/
#include "aria_utils.h"

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
