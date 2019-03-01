/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria primitive functions
**********************************************/
#include "aria_core.h"
#include <stdio.h>
#include <string.h>

void ariaCore(int            mode,
              ariaKey_t*     key,
              unsigned char* working_input_buffer,
              unsigned char* working_output_buffer) {
  char round;

  /* fixed round number */
  if (key->size == 128)
    round = 12;
  else if (key->size == 192)
    round = 14;
  else
    round = 16;
  DBG(fprintf(stdout, "rounder number: %d\n", round));
}