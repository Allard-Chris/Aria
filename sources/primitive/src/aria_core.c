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
#include <stdlib.h>
#include <string.h>

/* Put in aria_util.c file */
void cpy(u64 dest[2], u64 src[2]) {
  dest[0] = src[0];
  dest[1] = src[1];
}

int roundKeyGeneration(ariaKey_t* key, round_key_t* round_key) {
  fractional_t* fractional = malloc(sizeof(fractional_t));

  /* Initialisation figure 4 */
  if (key->size == 128) {
    cpy(fractional->CK[1], C1);
    cpy(fractional->CK[2], C2);
    cpy(fractional->CK[3], C3);

  } else if (key->size == 192) {
    cpy(fractional->CK[1], C2);
    cpy(fractional->CK[2], C3);
    cpy(fractional->CK[3], C1);

  } else if (key->size == 256) {
    cpy(fractional->CK[1], C3);
    cpy(fractional->CK[2], C1);
    cpy(fractional->CK[3], C2);

  } else {
    return -1;
  }

  /* Expension key generation */
  /*
  expansion_key_t* expansion_key = malloc(sizeof(expansion_key_t));
  KL = ;
  KR = ;
  expansion_key->w0 = key->key;
  expansion_key->w1 = F0() ^ ;
  expansion_key->w2 = FE() ^ expansion_key->w0;
  expansion_key->w3 = F0() ^ expansion_key->w1;
  */
  /* Round key generation */

  return 0;
}

int ariaCore(int            mode,
             ariaKey_t*     key,
             unsigned char* working_input_buffer,
             unsigned char* working_output_buffer,
             int            valid) {
  char     nb_round;
  state_t* state = NULL;

  /* fixed round number */
  if (key->size == 128)
    nb_round = 12;
  else if (key->size == 192)
    nb_round = 14;
  else /* 256-bits key size */
    nb_round = 16;

  DBG(fprintf(stdout, "Total number of round: %d\n", nb_round));

  /* create init state */
  state = (state_t*)malloc(sizeof(state_t));
  if (state == NULL) return -1;

  /* copy input buffer into state */
  memcpy(state, working_input_buffer, CHUNK_SIZE_OCTET);

  /* round key EK */
  round_key_t* round_key = malloc(sizeof(round_key_t));
  if (roundKeyGeneration(key, round_key) == -1) return -1;

  /* loop for all rounds */
  /* start at 1 to be egal with Aria specification description in PDF file */
  for (int i = 1; i <= nb_round; i++) {
    DBG(fprintf(stdout, "Current round: %d\n", i));
    /* XORing the round input and the round_key ek */
    /* if (valid) test output from XOR*/

    if (i % 2 != 0) DBG(fprintf(stdout, "Odd round\n"));
    /* ..substition layer type 1 */
    else
      DBG(fprintf(stdout, "Even round\n"));
    /* ..substition layer type 2 */
    /* Test result if Test variable is defined */

    /* if (i < nb_round)*/
    /* ..diffusion_layer */
    /* ..Test result if Test variable is defined */
  }
  /* Last XORing the round input and the round_key ek */

  /* write result in working_output_buffer*/
  memcpy(working_output_buffer, state, CHUNK_SIZE_OCTET);

  free(state);
  return 0;
}