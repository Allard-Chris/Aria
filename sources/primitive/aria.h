/*
 * ARIA crypto primitive structure
 */

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

extern const u8* S1_BOX[256];
extern const u8* S2_BOX[256];
extern const u8* S1_INVBOX[256];
extern const u8* S2_INVBOX[256];


typedef struct {
  unsigned char w0;
  unsigned char w1;
  unsigned char w2;
  unsigned char w3;
} expansion_key_t;

typedef struct {
  unsigned char key;
  unsigned char key_size;
  unsigned char nb_round;
  expansion_key_t* expansion_struct;
} key_t;

typedef struct {
  char* message;
  unsigned char current_round;
  key_t* key_struct;
} state_t;

// Init function, prepare each struct with parameters
state_t* Aria_init(char *plain_text, unsigned char *init_key);

// Main function for Aria encryption
char* Aria_encrypt (char *plain_text, unsigned char *key);

// Main function for Aria decryption
char* Aria_decryption (char *cipher_text, unsigned char *key);

// Function for global rounds operations
int Aria_round(state_t *init_state);

// Function for Step 1 inside rounds operations
int Aria_round_key_addition(state_t *current_state);

// Function for Step 2 inside rounds operations
int Aria_substitution_layer(state_t *current_state);

// Function for Step 3 inside rounds operations
int Aria_diffusion_layer(state_t *current_state);

// Function for last steps after rounds opertaion
int Aria_key_expansion(state_t *current_state);