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
u8* lCircleRotation(const u8* a, const unsigned int length) {
  u64       low_bytes = 0;
  u64       high_bytes = 0;
  u64       tmp_low_bytes = 0;
  u64       tmp_high_bytes = 0;
  static u8 output[CHUNK_16_OCTETS];

  /* first, converting array of 16 * u8 into 2 array of u64 */
  /* it's avoid limitation about shiffting with high length */
  u8ArrayToU64(a, &low_bytes, &high_bytes);

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
u8* rCircleRotation(const u8* a, const unsigned int length) {
  u64       low_bytes = 0;
  u64       high_bytes = 0;
  u64       tmp_low_bytes = 0;
  u64       tmp_high_bytes = 0;
  static u8 output[CHUNK_16_OCTETS];

  /* first, converting array of 16 * u8 into 2 array of u64 */
  /* it's avoid limitation about shiffting with high length */
  u8ArrayToU64(a, &low_bytes, &high_bytes);

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
void ariaSubstitutionLayer(u8* state, const int type) {
  for (int i = 0; i < CHUNK_16_OCTETS; i++) {
    state[i] = sl_type[type][i][(u8)state[i]];
  }
}

/* Diffusion layer of Aria map inputs of 16 bytes into matrix multiplication */
void ariaDiffusionLayer(u8* state) {
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

/* doing XOR between state and 128-bit round key */
void ariaXOR(const u8* a, const u8* b, u8* c) {
  for (int i = 0; i < CHUNK_16_OCTETS; i++) {
    c[i] = a[i] ^ b[i];
  }
}

/* feistelRound */
u8* ariaFeistelRound(u8* expansion_key, u8* constants_key, const int type) {
  static u8 output[CHUNK_16_OCTETS];
  memcpy(output, expansion_key, CHUNK_16_OCTETS);
  ariaXOR(output, constants_key, output);
  ariaSubstitutionLayer(output, type);
  ariaDiffusionLayer(output);
  return output;
}

/* create all Aria round key */
int ariaRoundKeyGeneration(const ariaKey_t* master_key,
                           round_key_t*     round_key) {
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
  memcpy(round_key->expansion_key[W0], master_key->key, CHUNK_16_OCTETS);
  u8 kr[CHUNK_16_OCTETS];
  memcpy(kr, (master_key->key + CHUNK_16_OCTETS), CHUNK_16_OCTETS - 1); /* copy
      last 128bit of Master Key */

  /* expansion key generation */
  ariaXOR(kr,
          ariaFeistelRound(round_key->expansion_key[W0],
                           round_key->constants_key[CK1], ODD),
          round_key->expansion_key[W1]);
  ariaXOR(round_key->expansion_key[W0],
          ariaFeistelRound(round_key->expansion_key[W1],
                           round_key->constants_key[CK2], EVEN),
          round_key->expansion_key[W2]);
  ariaXOR(round_key->expansion_key[W1],
          ariaFeistelRound(round_key->expansion_key[W2],
                           round_key->constants_key[CK3], ODD),
          round_key->expansion_key[W3]);

  /* round keys generation */
  /* ! Warning index 0 to 16 but in Aria paper it's 1 to 17  */
  ariaXOR(round_key->expansion_key[W0],
          rCircleRotation(round_key->expansion_key[W1], 19), round_key->ek[0]);
  ariaXOR(round_key->expansion_key[W1],
          rCircleRotation(round_key->expansion_key[W2], 19), round_key->ek[1]);
  ariaXOR(round_key->expansion_key[W2],
          rCircleRotation(round_key->expansion_key[W3], 19), round_key->ek[2]);
  ariaXOR(round_key->expansion_key[W3],
          rCircleRotation(round_key->expansion_key[W0], 19), round_key->ek[3]);
  ariaXOR(round_key->expansion_key[W0],
          rCircleRotation(round_key->expansion_key[W1], 31), round_key->ek[4]);
  ariaXOR(round_key->expansion_key[W1],
          rCircleRotation(round_key->expansion_key[W2], 31), round_key->ek[5]);
  ariaXOR(round_key->expansion_key[W2],
          rCircleRotation(round_key->expansion_key[W3], 31), round_key->ek[6]);
  ariaXOR(round_key->expansion_key[W3],
          rCircleRotation(round_key->expansion_key[W0], 31), round_key->ek[7]);
  ariaXOR(round_key->expansion_key[W0],
          lCircleRotation(round_key->expansion_key[W1], 61), round_key->ek[8]);
  ariaXOR(round_key->expansion_key[W1],
          lCircleRotation(round_key->expansion_key[W2], 61), round_key->ek[9]);
  ariaXOR(round_key->expansion_key[W2],
          lCircleRotation(round_key->expansion_key[W3], 61), round_key->ek[10]);
  ariaXOR(round_key->expansion_key[W3],
          lCircleRotation(round_key->expansion_key[W0], 61), round_key->ek[11]);
  ariaXOR(round_key->expansion_key[W0],
          lCircleRotation(round_key->expansion_key[W1], 31), round_key->ek[12]);
  if (master_key->size >= 128) {
    ariaXOR(round_key->expansion_key[W1],
            lCircleRotation(round_key->expansion_key[W2], 31),
            round_key->ek[13]);
    ariaXOR(round_key->expansion_key[W2],
            lCircleRotation(round_key->expansion_key[W3], 31),
            round_key->ek[14]);
  }
  if (master_key->size == 256) {
    ariaXOR(round_key->expansion_key[W3],
            lCircleRotation(round_key->expansion_key[W0], 31),
            round_key->ek[15]);
    ariaXOR(round_key->expansion_key[W0],
            lCircleRotation(round_key->expansion_key[W1], 19),
            round_key->ek[16]);
  }
  return 0;
}

int ariaCore(const int        mode,
             const ariaKey_t* master_key,
             const u8*        input_buffer,
             u8*              output_buffer) {
  char         nb_round = 0;
  int          result = 0;
  int          i;
  u8           state[CHUNK_16_OCTETS];
  round_key_t* round_key = NULL;

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

  /* allocation for round_key */
  round_key = (round_key_t*)malloc(sizeof(round_key_t));

  /* round key EK */
  if (round_key != NULL) {
    ariaRoundKeyGeneration(master_key, round_key);

    /* loop for all rounds */
    /* start at 1 to be egal with Aria specification description in PDF file */
    for (i = 1; i <= nb_round; i++) {
      DBG(fprintf(stdout, "Current round: %d\n", i));
      /* XORing the state input and the round_key ek */
      ariaXOR(state, round_key->ek[i - 1], state);

      if (i % 2 != 0) { /* ..substition layer type 1 */
        DBG(fprintf(stdout, "Odd round\n"));
        ariaSubstitutionLayer(state, ODD);
      } else { /* ..substition layer type 2 */
        DBG(fprintf(stdout, "Even round\n"));
        ariaSubstitutionLayer(state, EVEN);
      }

      /* ..diffusion_layer */
      if (i < nb_round) ariaDiffusionLayer(state);
    }
    DBG(fprintf(stdout, "Last round: %d\n", i++));

    /* Last XORing the state and the round_key ek */
    ariaXOR(state, round_key->ek[i - 1], state);

    /* write result in working_output_buffer*/
    memcpy(output_buffer, state, CHUNK_16_OCTETS);
  } else
    result = -1;

  free(round_key);
  return result;
}