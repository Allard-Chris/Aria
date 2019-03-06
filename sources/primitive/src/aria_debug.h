/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria debug statements
**********************************************/
#ifndef ARIA_DEBUG
#define ARIA_DEBUG

#ifndef DEBUG
#define DEBUG 1
#endif

#if (DEBUG)
#define DBG(_x)                                                            \
  (fprintf(stdout, "[FILE]:%s [FUNC]:%s [LINE]:%d - ", __FILE__, __func__, \
           __LINE__),                                                      \
   (void)(_x))
#else
#define DBG(_x) ((void)0)
#endif

#endif