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

int roundKeyGeneration(ariaKey_t* key, round_key_t* round_key) {
  /* Initialisation figure 4 */
  if (key->size == 128) {
    DBG(fprintf(stdout, "Constants key C1, C2, C3\n"));
    memcpy(round_key->constants_key[0], C1, CHUNK_SIZE_OCTET);
    memcpy(round_key->constants_key[1], C2, CHUNK_SIZE_OCTET);
    memcpy(round_key->constants_key[2], C3, CHUNK_SIZE_OCTET);
  } else if (key->size == 192) {
    DBG(fprintf(stdout, "Constants key C2, C3, C1\n"));
    memcpy(round_key->constants_key[0], C2, CHUNK_SIZE_OCTET);
    memcpy(round_key->constants_key[1], C3, CHUNK_SIZE_OCTET);
    memcpy(round_key->constants_key[2], C1, CHUNK_SIZE_OCTET);
  } else {
    DBG(fprintf(stdout, "Constants key C3, C1, C2\n"));
    memcpy(round_key->constants_key[0], C3, CHUNK_SIZE_OCTET);
    memcpy(round_key->constants_key[1], C1, CHUNK_SIZE_OCTET);
    memcpy(round_key->constants_key[2], C2, CHUNK_SIZE_OCTET);
  }

  /* Expension key generation *//*
  KL = ;
  KR = ;
  expansion_key->w0 = key->key;
  expansion_key->w1 = F0() ^ ;
  expansion_key->w2 = FE() ^ expansion_key->w0;
  expansion_key->w3 = F0() ^ expansion_key->w1;
  */

  /* Round key generation */
  // round_key_t* round_key = malloc(sizeof(round_key_t));
  // round_key->size = key->size - 1;

  /* from 0 to 15, be carefull on paper it's from 1 to 16 /!\
  if (round_key->size >= 12) {
    round_key->EK[0] = expansion_key->w0 ^ (expansion_key->w1 >> 19);
    round_key->EK[1] = expansion_key->w1 ^ (expansion_key->w2 >> 19);
    round_key->EK[2] = expansion_key->w2 ^ (expansion_key->w3 >> 19);
    round_key->EK[3] = (expansion_key->w0 >> 19) ^ expansion_key->w3;
    round_key->EK[4] = expansion_key->w0 ^ (expansion_key->w1 >> 31);
    round_key->EK[5] = expansion_key->w1 ^ (expansion_key->w1 >> 31);
    round_key->EK[6] = expansion_key->w2 ^ (expansion_key->w1 >> 31);
    round_key->EK[7] = (expansion_key->w0 >> 31) ^ expansion_key->w3;
    round_key->EK[8] = expansion_key->w0 ^ (expansion_key->w1 << 61);
    round_key->EK[9] = expansion_key->w1 ^ (expansion_key->w1 << 61);
    round_key->EK[10] = expansion_key->w2 ^ (expansion_key->w1 << 61);
    round_key->EK[11] = (expansion_key->w0 << 61) ^ expansion_key->w3;
    round_key->EK[12] = expansion_key->w0 ^ (expansion_key->w1 << 31);

    if (round_key->size >= 14) {
      round_key->EK[13] = expansion_key->w1 ^ (expansion_key->w1 << 31);
      round_key->EK[14] = expansion_key->w2 ^ (expansion_key->w1 << 31);

      if (round_key->size == 16) {
        round_key->EK[15] = (expansion_key->w0 << 31) ^ expansion_key->w3;
        round_key->EK[16] = expansion_key->w0 ^ (expansion_key->w1 << 19);

      }
    }
  }
  */
  return 0;
}

int ariaCore(int            mode,
             ariaKey_t*     key,
             unsigned char* working_input_buffer,
             unsigned char* working_output_buffer) {
  char             nb_round;
  int              result = 0;
  u8               state[CHUNK_SIZE_OCTET];
  expansion_key_t* expansion_key;
  round_key_t*     round_key;

  /* fixed round number */
  if (key->size == 128)
    nb_round = 12;
  else if (key->size == 192)
    nb_round = 14;
  else /* 256-bits key size */
    nb_round = 16;
  DBG(fprintf(stdout, "Total number of round: %d\n", nb_round));

  /* copy input buffer into state */
  memcpy(state, working_input_buffer, CHUNK_SIZE_OCTET);

  /* allocation for round_key and expansion_key */
  round_key = (round_key_t*)malloc(sizeof(round_key_t));
  expansion_key = (expansion_key_t*)malloc(sizeof(expansion_key_t));

  /* round key EK */
  if ((round_key != NULL) && (expansion_key != NULL)) {
    round_key->expansion_key = expansion_key;
    roundKeyGeneration(key, round_key);

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
  } else
    result = -1;

  free(round_key);
  free(expansion_key);
  return result;
}