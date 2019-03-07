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

/* doign left circle rotation on array values */
u8 lCircleRotation(const u8* input, const unsigned int length) {
  u64 low_bytes = 0;
  u64 high_bytes = 0;
  u64 tmp_low_bytes = 0;
  u64 tmp_high_bytes = 0;
  u8  output[CHUNK_16_OCTETS];

  /* copy input into output */
  memcpy(output, input, CHUNK_16_OCTETS);

  /* first, converting array of 16 * u8 into 2 array of u64 */
  /* it's avoid limitation about shiffting with high length */
  u8ArrayToU64(output, &low_bytes, &high_bytes);

  /* doing circle shiffting */
  tmp_low_bytes = low_bytes;
  tmp_high_bytes = high_bytes;

  low_bytes <<= length;
  tmp_low_bytes >>= ((sizeof(u64) * 8) - length);
  high_bytes <<= length;
  tmp_high_bytes >>= ((sizeof(u64) * 8) - length);

  low_bytes ^= tmp_high_bytes;
  high_bytes ^= tmp_low_bytes;

  /* reconvert 2 array of u64 into one array of 16 * u8 */
  u64ToU8Array(output, &low_bytes, &high_bytes);

  return output;
}

/* doign right circle rotation on array values */
u8 rCircleRotation(const u8* input, const unsigned int length) {
  u64 low_bytes = 0;
  u64 high_bytes = 0;
  u64 tmp_low_bytes = 0;
  u64 tmp_high_bytes = 0;
  u8  output[CHUNK_16_OCTETS];

  /* copy input into output */
  memcpy(output, input, CHUNK_16_OCTETS);

  /* first, converting array of 16 * u8 into 2 array of u64 */
  /* it's avoid limitation about shiffting with high length */
  u8ArrayToU64(output, &low_bytes, &high_bytes);

  /* doing circle shiffting */
  tmp_low_bytes = low_bytes;
  tmp_high_bytes = high_bytes;

  low_bytes >>= length;
  tmp_low_bytes <<= ((sizeof(u64) * 8) - length);
  high_bytes >>= length;
  tmp_high_bytes <<= ((sizeof(u64) * 8) - length);

  low_bytes ^= tmp_high_bytes;
  high_bytes ^= tmp_low_bytes;

  /* reconvert 2 array of u64 into one array of 16 * u8 */
  u64ToU8Array(output, &low_bytes, &high_bytes);

  return output;
}

/* send state array into SBOX */
void substituionLayer(u8* state[], int type) {
  if (type == ODD) {
    for (int i = 0; i < CHUNK_16_OCTETS; i++) {
      *state[i] = sl_type1[i][(u8)*state[i]];
    }
  } else {
    for (int i = 0; i < CHUNK_16_OCTETS; i++) {
      *state[i] = sl_type2[i][(u8)*state[i]];
    }
  }
}

/* Diffusion layer of Aria map inputs of 16 bytes into matrix multiplication */
void diffusionLayer(u8* state) {
  u8 copy_state[CHUNK_16_OCTETS];
  memcpy(copy_state, state, CHUNK_16_OCTETS);
  state[0] = copy_state[3] ^ copy_state[4] ^ copy_state[6] ^ copy_state[8] ^
             copy_state[9] ^ copy_state[13] ^ copy_state[14];
  state[1] = copy_state[2] ^ copy_state[5] ^ copy_state[7] ^ copy_state[8] ^
             copy_state[9] ^ copy_state[12] ^ copy_state[15];
  state[2] = copy_state[1] ^ copy_state[4] ^ copy_state[6] ^ copy_state[10] ^
             copy_state[11] ^ copy_state[12] ^ copy_state[15];
  state[3] = copy_state[0] ^ copy_state[5] ^ copy_state[7] ^ copy_state[10] ^
             copy_state[11] ^ copy_state[13] ^ copy_state[14];
  state[4] = copy_state[0] ^ copy_state[2] ^ copy_state[5] ^ copy_state[8] ^
             copy_state[11] ^ copy_state[14] ^ copy_state[15];
  state[5] = copy_state[1] ^ copy_state[3] ^ copy_state[4] ^ copy_state[9] ^
             copy_state[10] ^ copy_state[14] ^ copy_state[15];
  state[6] = copy_state[0] ^ copy_state[2] ^ copy_state[7] ^ copy_state[9] ^
             copy_state[10] ^ copy_state[12] ^ copy_state[13];
  state[7] = copy_state[1] ^ copy_state[3] ^ copy_state[6] ^ copy_state[8] ^
             copy_state[11] ^ copy_state[12] ^ copy_state[13];
  state[8] = copy_state[0] ^ copy_state[1] ^ copy_state[4] ^ copy_state[7] ^
             copy_state[10] ^ copy_state[13] ^ copy_state[15];
  state[9] = copy_state[0] ^ copy_state[1] ^ copy_state[5] ^ copy_state[6] ^
             copy_state[11] ^ copy_state[12] ^ copy_state[14];
  state[10] = copy_state[2] ^ copy_state[3] ^ copy_state[5] ^ copy_state[6] ^
              copy_state[8] ^ copy_state[13] ^ copy_state[15];
  state[11] = copy_state[2] ^ copy_state[3] ^ copy_state[4] ^ copy_state[7] ^
              copy_state[9] ^ copy_state[12] ^ copy_state[14];
  state[12] = copy_state[1] ^ copy_state[2] ^ copy_state[6] ^ copy_state[7] ^
              copy_state[9] ^ copy_state[11] ^ copy_state[12];
  state[13] = copy_state[0] ^ copy_state[3] ^ copy_state[6] ^ copy_state[7] ^
              copy_state[8] ^ copy_state[10] ^ copy_state[13];
  state[14] = copy_state[0] ^ copy_state[3] ^ copy_state[4] ^ copy_state[5] ^
              copy_state[9] ^ copy_state[11] ^ copy_state[14];
  state[15] = copy_state[1] ^ copy_state[2] ^ copy_state[4] ^ copy_state[5] ^
              copy_state[8] ^ copy_state[10] ^ copy_state[15];
}
/*
void xor (u8 output[16], u8 input1[16], u8 input2[16]) {
}


u8* fe(u8 w[CHUNK_SIZE_OCTET], u8 ck[CHUNK_SIZE_OCTET]) {
  u8 return_value[CHUNK_SIZE_OCTET];
  u8 tmp[CHUNK_SIZE_OCTET];
  u8 tmp2[CHUNK_SIZE_OCTET];

  xor(tmp, w, ck);

  sL2(tmp2, tmp);
  diffusion(return_value, tmp);
}

u8* fo(u8 w[CHUNK_SIZE_OCTET], u8 ck[CHUNK_SIZE_OCTET]) {
  u8 return_value[CHUNK_SIZE_OCTET];
  u8 tmp[CHUNK_SIZE_OCTET];

  xor(tmp, w, ck);
    for (int i = 0; i < 16; i++)
      tmp[i] = S_BOX[i % 4][tmp[i]];

  diffusion(return_value, tmp);
}
*/
int roundKeyGeneration(const ariaKey_t* master_key, round_key_t* round_key) {
  /* Initialisation figure 4 */
  if (master_key->size == 128) {
    DBG(fprintf(stdout, "Constants key C1, C2, C3\n"));
    memcpy(round_key->constants_key[0], C1, CHUNK_16_OCTETS);
    memcpy(round_key->constants_key[1], C2, CHUNK_16_OCTETS);
    memcpy(round_key->constants_key[2], C3, CHUNK_16_OCTETS);
  } else if (master_key->size == 192) {
    DBG(fprintf(stdout, "Constants key C2, C3, C1\n"));
    memcpy(round_key->constants_key[0], C2, CHUNK_16_OCTETS);
    memcpy(round_key->constants_key[1], C3, CHUNK_16_OCTETS);
    memcpy(round_key->constants_key[2], C1, CHUNK_16_OCTETS);
  } else {
    DBG(fprintf(stdout, "Constants key C3, C1, C2\n"));
    memcpy(round_key->constants_key[0], C3, CHUNK_16_OCTETS);
    memcpy(round_key->constants_key[1], C1, CHUNK_16_OCTETS);
    memcpy(round_key->constants_key[2], C2, CHUNK_16_OCTETS);
  }

  /* constant kl and kr generation */
  /* w0 = KL so avoid double array, and copy direct to w0*/
  /* copy first 128bit of Master Key */
  memcpy(round_key->expansion_key->w0, master_key->key, CHUNK_16_OCTETS);
  u8 kr[CHUNK_16_OCTETS];
  memcpy(kr, (master_key->key + CHUNK_16_OCTETS), CHUNK_16_OCTETS - 1); /* copy
      last 128bit of Master Key */

  //  /* expansion key generation
  //      expansion_key->w0 = key->key;
  //      expansion_key->w1 = FO(round_key->expansion_key->w0,
  //     round_key->constants_key[0]) ^ kr; expansion_key->w2 =
  //     FE(round_key->expansion_key->w1, round_key->constants_key[1]) ^
  //     expansion_key->w0; expansion_key->w3 = FO(round_key->expansion_key->w2,
  //     round_key->constants_key[2]) ^ expansion_key->w1;
  //      */
  //
  //  /* Round key generation */
  //  // round_key_t* round_key = malloc(sizeof(round_key_t));
  //  // round_key->size = key->size - 1;
  //
  //  /* from 0 to 15, be carefull on paper it's from 1 to 16 /!\
//  if (round_key->size >= 12) {
  //    round_key->EK[0] = expansion_key->w0 ^ (expansion_key->w1 >> 19);
  //    round_key->EK[1] = expansion_key->w1 ^ (expansion_key->w2 >> 19);
  //    round_key->EK[2] = expansion_key->w2 ^ (expansion_key->w3 >> 19);
  //    round_key->EK[3] = (expansion_key->w0 >> 19) ^ expansion_key->w3;
  //    round_key->EK[4] = expansion_key->w0 ^ (expansion_key->w1 >> 31);
  //    round_key->EK[5] = expansion_key->w1 ^ (expansion_key->w1 >> 31);
  //    round_key->EK[6] = expansion_key->w2 ^ (expansion_key->w1 >> 31);
  //    round_key->EK[7] = (expansion_key->w0 >> 31) ^ expansion_key->w3;
  //    round_key->EK[8] = expansion_key->w0 ^ (expansion_key->w1 << 61);
  //    round_key->EK[9] = expansion_key->w1 ^ (expansion_key->w1 << 61);
  //    round_key->EK[10] = expansion_key->w2 ^ (expansion_key->w1 << 61);
  //    round_key->EK[11] = (expansion_key->w0 << 61) ^ expansion_key->w3;
  //    round_key->EK[12] = expansion_key->w0 ^ (expansion_key->w1 << 31);
  //
  //    if (round_key->size >= 14) {
  //      round_key->EK[13] = expansion_key->w1 ^ (expansion_key->w1 << 31);
  //      round_key->EK[14] = expansion_key->w2 ^ (expansion_key->w1 << 31);
  //
  //      if (round_key->size == 16) {
  //        round_key->EK[15] = (expansion_key->w0 << 31) ^ expansion_key->w3;
  //        round_key->EK[16] = expansion_key->w0 ^ (expansion_key->w1 << 19);
  //
  //      }
  //    }
  //  }
  //  */
  return 0;
}

int ariaCore(const int            mode,
             const ariaKey_t*     master_key,
             const unsigned char* input_buffer,
             unsigned char*       output_buffer) {
  char             nb_round;
  int              result = 0;
  u8               state[CHUNK_16_OCTETS];
  expansion_key_t* expansion_key;
  round_key_t*     round_key;

  /* fixed round number */
  if (master_key->size == 128)
    nb_round = 12;
  else if (master_key->size == 192)
    nb_round = 14;
  else /* 256-bits master key size */
    nb_round = 16;
  DBG(fprintf(stdout, "Total number of round: %d\n", nb_round));

  /* copy input buffer into state */
  memcpy(state, input_buffer, CHUNK_16_OCTETS);

  /* allocation for round_key and expansion_key */
  round_key = (round_key_t*)malloc(sizeof(round_key_t));
  expansion_key = (expansion_key_t*)malloc(sizeof(expansion_key_t));
  diffusionLayer(state);

  /* round key EK */
  if ((round_key != NULL) && (expansion_key != NULL)) {
    round_key->expansion_key = expansion_key;
    roundKeyGeneration(master_key, round_key);

    /* loop for all rounds */
    /* start at 1 to be egal with Aria specification description in PDF file
     */
    int i;
    for (i = 1; i <= nb_round; i++) {
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
    DBG(fprintf(stdout, "Last round: %d\n", i++));

    /* write result in working_output_buffer*/
    memcpy(output_buffer, state, CHUNK_16_OCTETS);
  } else
    result = -1;

  free(round_key);
  free(expansion_key);
  return result;
}