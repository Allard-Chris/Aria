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

// Init function, prepare each struct with parameters
state_t* ariaInit(char* plain_text, unsigned char* init_key);

// Main function for Aria encryption
char* ariaEncrypt(char* plain_text, unsigned char* key);

// Main function for Aria decryption
char* ariaDecryption(char* cipher_text, unsigned char* key);

// Function for global rounds operations
int ariaRound(state_t* init_state);

// Function for Step 1 inside rounds operations
int ariaRoundKeyAddition(state_t* current_state);

// Function for Step 2 inside rounds operations
int ariaSubstitutionLayer(state_t* current_state);

// Function for Step 3 inside rounds operations
int ariaDiffusionLayer(state_t* current_state);

// Function for last steps after rounds opertaion
int ariaKeyExpansion(state_t* current_state);

#endif