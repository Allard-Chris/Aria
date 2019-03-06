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
void lCircleRotation(unsigned char* array, const unsigned int length) {
  u64  low_bytes = 0;
  u64  high_bytes = 0;
  u64  tmp_low_bytes = 0;
  u64  tmp_high_bytes = 0;
  u64* p_low_bytes = &low_bytes;
  u64* p_high_bytes = &high_bytes;

  /* first, converting array of 16 * u8 into 2 array of u64 */
  /* it's avoid limitation about shiffting with high length */
  u8ArrayToU64(array, p_low_bytes, p_high_bytes);

  /* doing circle shiffting */
  /* example to understand : */
  /* start with: [x1, x2, x3, x4, x5, x6, x7, x8] and shift << 3 */
  /* result    : [x4, x5, x6, x7, x8, 0, 0, 0] */
  /* now doing : [x1, x2, x3, x4, x5, x6, x7, x8] shiffted by 8 - 3 */
  /* result    : [0, 0, 0, 0, 0, x1, x2, x3] */
  /* now doing : [0, 0, 0, 0, 0, x1, x2, x3] XOR [x4, x5, x6, x7, x8, 0, 0, 0]*/
  /* result    : [x4,x5, x6, x7, x8, x1, x2, x3] */
  //  tmp_low_bytes = *p_low_bytes;
  //  tmp_high_bytes = *p_high_bytes;
  //
  //  *p_low_bytes <<= length;
  //  tmp_low_bytes >>= ((sizeof(u64) * 8) - length);
  //  *p_high_bytes <<= length;
  //  tmp_high_bytes >>= ((sizeof(u64) * 8) - length);
  //
  //  *p_low_bytes = *p_low_bytes || tmp_low_bytes;
  //  *p_high_bytes = *p_high_bytes || tmp_high_bytes;

  /* reconvert 2 array of u64 into one array of 16 * u8 */
  u64ToU8Array(array, p_low_bytes, p_high_bytes);
}

/* doign right circle rotation on array values */
void rCircleRotation(unsigned char* array, const unsigned int length) {
  u64  left = 0;
  u64  right = 0;
  u64  tmp_left = 0;
  u64  tmp_right = 0;
  u64* p_left = &left;
  u64* p_right = &right;

  /* first, converting array of 16 * u8 into 2 array of u64 */
  /* it's avoid limitation about shiffting with high length */
  u8ArrayToU64(array, p_left, p_right);

  /* doing circle shiffting */
  /* example in lCircleRotation function */
  // tmp_left = *p_left;
  // tmp_right = *p_right;

  //*p_left = *p_left >> length;
  // tmp_left = tmp_left << ((sizeof(u64) - length));
  //*p_right = *p_right >> length;
  // tmp_right = tmp_right << ((sizeof(u64) - length));

  //*p_left = *p_left || tmp_left;
  //*p_right = *p_right || tmp_right;

  //  /* reconvert 2 array of u64 into one array of 16 * u8 */
  u64ToU8Array(array, p_left, p_right);
}

/*
void diffusion(u8 output[CHUNK_SIZE_OCTET], const u8 input[CHUNK_SIZE_OCTET]) {
  output[0] = input[3] ^ input[4] ^ input[6] ^ input[8] ^ input[9] ^ input[13] ^
              input[14];
  output[1] = input[2] ^ input[5] ^ input[7] ^ input[8] ^ input[9] ^ input[12] ^
              input[15];
  output[2] = input[1] ^ input[4] ^ input[6] ^ input[10] ^ input[11] ^
              input[12] ^ input[15];
  output[3] = input[0] ^ input[5] ^ input[7] ^ input[10] ^ input[11] ^
              input[13] ^ input[14];
  output[4] = input[0] ^ input[2] ^ input[5] ^ input[8] ^ input[11] ^
              input[14] ^ input[15];
  output[5] = input[1] ^ input[3] ^ input[4] ^ input[9] ^ input[10] ^
              input[14] ^ input[15];
  output[6] = input[0] ^ input[2] ^ input[7] ^ input[9] ^ input[10] ^
              input[12] ^ input[13];
  output[7] = input[1] ^ input[3] ^ input[6] ^ input[8] ^ input[11] ^
              input[12] ^ input[13];
  output[8] = input[0] ^ input[1] ^ input[4] ^ input[7] ^ input[10] ^
              input[13] ^ input[15];
  output[9] = input[0] ^ input[1] ^ input[5] ^ input[6] ^ input[11] ^
              input[12] ^ input[14];
  output[10] = input[2] ^ input[3] ^ input[5] ^ input[6] ^ input[8] ^
               input[13] ^ input[15];
  output[11] = input[2] ^ input[3] ^ input[4] ^ input[7] ^ input[9] ^
               input[12] ^ input[14];
  output[12] = input[1] ^ input[2] ^ input[6] ^ input[7] ^ input[9] ^
               input[11] ^ input[12];
  output[13] = input[0] ^ input[3] ^ input[6] ^ input[7] ^ input[8] ^
               input[10] ^ input[13];
  output[14] = input[0] ^ input[3] ^ input[4] ^ input[5] ^ input[9] ^
               input[11] ^ input[14];
  output[15] = input[1] ^ input[2] ^ input[4] ^ input[5] ^ input[8] ^
               input[10] ^ input[15];
}

void xor (u8 output[16], u8 input1[16], u8 input2[16]) {
}

void sL2(u8 output[16], const u8 input[16]) {
  for (int i = 0; i < 16; i++) {
     if (i % 4 < 2)
      output[i] = S_BOX[(i % 4) + 2][input[i]];
    else if (i % 4 >= 2)
      output[i] = S_BOX[(i % 4) - 2][input[i]];
  }
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
  DBG(printBuffer(round_key->expansion_key->w0, CHUNK_16_OCTETS));
  lCircleRotation(round_key->expansion_key->w0, 16);
  DBG(printBuffer(round_key->expansion_key->w0, CHUNK_16_OCTETS));
  // rCircleRotation(round_key->expansion_key->w0, 16);
  // DBG(printBuffer(round_key->expansion_key->w0, CHUNK_16_OCTETS));
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

  /* round key EK */
  if ((round_key != NULL) && (expansion_key != NULL)) {
    round_key->expansion_key = expansion_key;
    roundKeyGeneration(master_key, round_key);

    /* loop for all rounds */
    /* start at 1 to be egal with Aria specification description in PDF file
     */
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
    memcpy(output_buffer, state, CHUNK_16_OCTETS);
  } else
    result = -1;

  free(round_key);
  free(expansion_key);
  return result;
}