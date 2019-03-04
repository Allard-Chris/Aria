/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria primitive functions
**********************************************/
#ifndef ARIA_CORE
#define ARIA_CORE
#include "aria_const.h"
#include "aria_debug.h"
#include "aria_type.h"

/* global function for operations */
/* valid parameter only to test aria algorithm with plaintext.txt input */
/* return 0 : all is ok, -1 error during process */
int ariaCore(int            mode,
             ariaKey_t*     key,
             unsigned char* working_input_buffer,
             unsigned char* working_output_buffer,
             int            valid);

/*
// Function for Step 1 inside rounds operations
int ariaRoundKeyAddition(state_t* current_state);

// Function for Step 2 inside rounds operations
int ariaSubstitutionLayer(state_t* current_state);

// Function for Step 3 inside rounds operations
int ariaDiffusionLayer(state_t* current_state);

// Function for last steps after rounds opertaion
int ariaKeyExpansion(state_t* current_state);
*/
#endif
