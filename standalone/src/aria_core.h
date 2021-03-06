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
#include "aria_type.h"
#include "aria_utils.h"

/* global function for operations */
/* valid parameter only to test aria algorithm with plaintext.txt input */
/* return 0 : all is ok, -1 error during process */
int ariaCore(const int        mode,
             const ariaKey_t* key,
             const u8*        input_buffer,
             u8*              output_buffer);

/* doign left circle rotation on a values, return u8 array */
u8* lCircleRotation(const u8* a, const unsigned int length);

/* doign right circle rotation on a values, return u8 array */
u8* rCircleRotation(const u8* a, const unsigned int length);

/* doing XOR between a and b, results in output */
void ariaXOR(const u8* a, const u8* b, u8* c);

/* Function for Step 1 inside rounds operations */
int ariaRoundKeyGeneration(const ariaKey_t* master_key, round_key_t* round_key);

/* Function for Step 2 inside rounds operations */
void ariaSubstitutionLayer(u8* state, const int type);

/* Function for Step 3 inside rounds operations */
void ariaDiffusionLayer(u8* state);

/* Function for running Feistel round */
u8* ariaFeistelRound(u8* expansion_key, u8* constants_key, const int type);

#endif /* ARIA_CORE */