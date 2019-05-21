/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria primitive
**********************************************/
#include "openssl/aria.h"
#include "aria_locl.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <openssl/opensslconf.h>

/* convert array of 16 * u8 into 2 u64 array */
void u8ArrayToU64(const u8* input, u64* low_bytes, u64* high_bytes) {
    for (int i = 0; i < (ARIA_BLOCK_SIZE / 2); i++) {
        *low_bytes <<= 8;
        *low_bytes += (u8)input[i];
    }
    for (int i = (ARIA_BLOCK_SIZE / 2); i < ARIA_BLOCK_SIZE; i++) {
        *high_bytes <<= 8;
        *high_bytes += (u8)input[i];
    }
}

/* convert 2 array of u64 into array of 16 * 8 */
void u64ToU8Array(u8* output, const u64* low_bytes, const u64* high_bytes) {
    u64 tmp_low_bytes     = *low_bytes;
    u64 tmp_high_bytes    = *high_bytes;
    for (int i = ((ARIA_BLOCK_SIZE / 2) - 1); i >= 0; i--) {
        output[i] = (u8)tmp_low_bytes;
        tmp_low_bytes >>= 8;
    }
    for (int i = (ARIA_BLOCK_SIZE - 1); i >= (ARIA_BLOCK_SIZE / 2); i--) {
        output[i] = (u8)tmp_high_bytes;
        tmp_high_bytes >>= 8;
    }
}

/* doing left circle rotation on array values */
u8* lCircleRotation(const u8* a, const unsigned int length) {
    u64 low_bytes       = 0;
    u64 high_bytes      = 0;
    u64 tmp_low_bytes   = 0;
    u64 tmp_high_bytes  = 0;
    static u8 output[ARIA_BLOCK_SIZE];

    /* first, converting array of 16 * u8 into 2 array of u64 */
    /* it's avoid limitation about shiffting with high length */
    u8ArrayToU64(a, &low_bytes, &high_bytes);

    /* doing circle shiffting */
    tmp_low_bytes   = low_bytes;
    tmp_high_bytes  = high_bytes;

    low_bytes       <<= length;
    tmp_low_bytes   >>= ((sizeof(u64) * 8) - length);
    high_bytes      <<= length;
    tmp_high_bytes  >>= ((sizeof(u64) * 8) - length);

    low_bytes   |= tmp_high_bytes;
    high_bytes  |= tmp_low_bytes;

    /* reconvert 2 array of u64 into one array of 16 * u8 */
    u64ToU8Array(output, &low_bytes, &high_bytes);

    return output;
}

/* doign right circle rotation on array values */
u8* rCircleRotation(const u8* a, const unsigned int length) {
    u64 low_bytes       = 0;
    u64 high_bytes      = 0;
    u64 tmp_low_bytes   = 0;
    u64 tmp_high_bytes  = 0;
    static u8 output[ARIA_BLOCK_SIZE];

    /* first, converting array of 16 * u8 into 2 array of u64 */
    /* it's avoid limitation about shiffting with high length */
    u8ArrayToU64(a, &low_bytes, &high_bytes);

    /* doing circle shiffting */
    tmp_low_bytes   = low_bytes;
    tmp_high_bytes  = high_bytes;

    low_bytes       >>= length;
    tmp_low_bytes   <<= ((sizeof(u64) * 8) - length);
    high_bytes      >>= length;
    tmp_high_bytes  <<= ((sizeof(u64) * 8) - length);

    low_bytes   |= tmp_high_bytes;
    high_bytes  |= tmp_low_bytes;

    /* reconvert 2 array of u64 into one array of 16 * u8 */
    u64ToU8Array(output, &low_bytes, &high_bytes);

    return output;
}

/* doing XOR between state and 128-bit round key */
void ariaXOR(const u8* a, const u8* b, u8* c){
    for (size_t i = 0; i < ARIA_BLOCK_SIZE; i++) {
        c[i] = a[i] ^ b[i];
    }
}

/* send state array into SBOX */
void ariaSubstitutionLayer(u8* state, const int type){
    for (size_t i = 0; i < ARIA_BLOCK_SIZE; i++) {
        state[i] = sl_type[type][i][(u8)state[i]];
    }
}

/* Diffusion layer of Aria map inputs of 16 bytes into matrix multiplication */
void ariaDiffusionLayer(u8* state) {
    u8 copy_state[ARIA_BLOCK_SIZE];
    memcpy(copy_state, state, ARIA_BLOCK_SIZE);
    state[0] =  copy_state[3] ^ copy_state[4] ^ copy_state[6] ^ copy_state[8] ^
                copy_state[9] ^ copy_state[13] ^ copy_state[14];
    state[1] =  copy_state[2] ^ copy_state[5] ^ copy_state[7] ^ copy_state[8] ^
                copy_state[9] ^ copy_state[12] ^ copy_state[15];
    state[2] =  copy_state[1] ^ copy_state[4] ^ copy_state[6] ^ copy_state[10] ^
                copy_state[11] ^ copy_state[12] ^ copy_state[15];
    state[3] =  copy_state[0] ^ copy_state[5] ^ copy_state[7] ^ copy_state[10] ^
                copy_state[11] ^ copy_state[13] ^ copy_state[14];
    state[4] =  copy_state[0] ^ copy_state[2] ^ copy_state[5] ^ copy_state[8] ^
                copy_state[11] ^ copy_state[14] ^ copy_state[15];
    state[5] =  copy_state[1] ^ copy_state[3] ^ copy_state[4] ^ copy_state[9] ^
                copy_state[10] ^ copy_state[14] ^ copy_state[15];
    state[6] =  copy_state[0] ^ copy_state[2] ^ copy_state[7] ^ copy_state[9] ^
                copy_state[10] ^ copy_state[12] ^ copy_state[13];
    state[7] =  copy_state[1] ^ copy_state[3] ^ copy_state[6] ^ copy_state[8] ^
                copy_state[11] ^ copy_state[12] ^ copy_state[13];
    state[8] =  copy_state[0] ^ copy_state[1] ^ copy_state[4] ^ copy_state[7] ^
                copy_state[10] ^ copy_state[13] ^ copy_state[15];
    state[9] =  copy_state[0] ^ copy_state[1] ^ copy_state[5] ^ copy_state[6] ^
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

/* feistelRound */
u8* ariaFeistelRound(u8* expansion_key, u8* constants_key, const int type){
    static u8 output[ARIA_BLOCK_SIZE];
    memcpy(output, expansion_key, ARIA_BLOCK_SIZE);
    ariaXOR(output, constants_key, output);
    ariaSubstitutionLayer(output, type);
    ariaDiffusionLayer(output);
    return output;
}

int Aria_set_encrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key){
    /* First check arguments */
    if (!userKey || !key)
        return -1;
    if (bits != 128 && bits != 192 && bits != 256)
        return -2;

    /* constant kl and kr generation */
    /* w0 = KL so avoid double array, and copy direct to w0*/
    /* copy first 128bit of Master Key */
    for (size_t i = 0; i < ARIA_BLOCK_SIZE; i++) {
        key->wk[0][i] = *(userKey + i);
        key->wk[1][i] = 0;
    }

    /* Initialisation constants */
    if (bits == 128) { /* KL defined and KR empty */
        key->rounds=13;
        memcpy(key->ck[CK1], C1, ARIA_BLOCK_SIZE);
        memcpy(key->ck[CK2], C2, ARIA_BLOCK_SIZE);
        memcpy(key->ck[CK3], C3, ARIA_BLOCK_SIZE);
    } else if (bits == 192) {
        for (size_t i = 0; i < (ARIA_BLOCK_SIZE/2); i++) {
            /* Take 64 bits for KR filled with 0*/
            key->wk[1][i] = *(userKey + (i+16));
        }
        key->rounds=15;
        memcpy(key->ck[CK1], C2, ARIA_BLOCK_SIZE);
        memcpy(key->ck[CK2], C3, ARIA_BLOCK_SIZE);
        memcpy(key->ck[CK3], C1, ARIA_BLOCK_SIZE);
    } else {
        for (size_t i = 0; i < (ARIA_BLOCK_SIZE/2); i++) {
            /* Take 128 bits for KR */
            key->wk[1][i+8] = *(userKey + (i+24));
        }
        key->rounds=17;
        memcpy(key->ck[CK1], C3, ARIA_BLOCK_SIZE);
        memcpy(key->ck[CK2], C1, ARIA_BLOCK_SIZE);
        memcpy(key->ck[CK3], C2, ARIA_BLOCK_SIZE);
    }

    /* expansion key generation */
    /* W1 */
    ariaXOR(key->wk[W1],
        ariaFeistelRound(key->wk[W0], key->ck[CK1], ODD), key->wk[W1]);
    /* W2 */
    ariaXOR(key->wk[W0],
        ariaFeistelRound(key->wk[W1], key->ck[CK2], EVEN), key->wk[W2]);
    /* W3 */
    ariaXOR(key->wk[W1],
        ariaFeistelRound(key->wk[W2], key->ck[CK3], ODD), key->wk[W3]);

    /* round keys generation */
    /* ! Warning: index 0 to 16 but in Aria paper it's 1 to 17 */
    ariaXOR(key->wk[W0], rCircleRotation(key->wk[W1], 19), key->rd_key[0]);
    ariaXOR(key->wk[W1], rCircleRotation(key->wk[W2], 19), key->rd_key[1]);
    ariaXOR(key->wk[W2], rCircleRotation(key->wk[W3], 19), key->rd_key[2]);
    ariaXOR(key->wk[W3], rCircleRotation(key->wk[W0], 19), key->rd_key[3]);
    ariaXOR(key->wk[W0], rCircleRotation(key->wk[W1], 31), key->rd_key[4]);
    ariaXOR(key->wk[W1], rCircleRotation(key->wk[W2], 31), key->rd_key[5]);
    ariaXOR(key->wk[W2], rCircleRotation(key->wk[W2], 31), key->rd_key[6]);
    ariaXOR(key->wk[W3], rCircleRotation(key->wk[W0], 31), key->rd_key[7]);
    ariaXOR(key->wk[W0], lCircleRotation(key->wk[W1], 61), key->rd_key[8]);
    ariaXOR(key->wk[W1], lCircleRotation(key->wk[W2], 61), key->rd_key[9]);
    ariaXOR(key->wk[W2], lCircleRotation(key->wk[W3], 61), key->rd_key[10]);
    ariaXOR(key->wk[W3], lCircleRotation(key->wk[W0], 61), key->rd_key[11]);
    ariaXOR(key->wk[W0], lCircleRotation(key->wk[W1], 31), key->rd_key[12]);

    if (bits >= 128) {
        ariaXOR(key->wk[W1], lCircleRotation(key->wk[W2], 31), key->rd_key[13]);
        ariaXOR(key->wk[W2], lCircleRotation(key->wk[W3], 31), key->rd_key[14]);
    }
    if (bits == 256) {
        ariaXOR(key->wk[W3], lCircleRotation(key->wk[W0], 31), key->rd_key[15]);
        ariaXOR(key->wk[W0], lCircleRotation(key->wk[W1], 19), key->rd_key[16]);
    }
    return 0;
}

int Aria_set_decrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key){
    int status;

    /* first, start with an encryption schedule */
    status = Aria_set_encrypt_key(userKey, bits, key);
    if (status < 0)
        return status;

    u8 temp_rd_key[ARIA_MAX_ROUND][ARIA_BLOCK_SIZE];
    memcpy(temp_rd_key, key->rd_key, sizeof(key->rd_key));
    for (size_t i = key->rounds; i >= 0; i--) {
        if ((i != key->rounds) & (i != 0)){
            ariaDiffusionLayer(key->rd_key[(key->rounds - i)]);
        }
        memcpy(key->rd_key[(key->rounds - i)], temp_rd_key[i],
        sizeof(key->rd_key[i]));
    }
    return 0;
}


void Aria_encrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key) {
    u8 input[ARIA_BLOCK_SIZE];
    u8 state[ARIA_BLOCK_SIZE];
    size_t i;
    for (i = 0; i < ARIA_BLOCK_SIZE; i++) {
        input[i] = *(in + i);
    }

    memcpy(state, input, ARIA_BLOCK_SIZE);

    for (i = 0; i < key->rounds; i++) {
        /* loop for all rounds */
        ariaXOR(state, key->rd_key[i], state);

        if (i % 2 != 0) { /* substituion layer type 1 */
            ariaSubstitutionLayer(state, ODD);
        } else { /* substituion layer type 2 */
        ariaSubstitutionLayer(state, EVEN);
        }

        if (i < key->rounds) ariaDiffusionLayer(state);
    }
    /* Last XORing the state and the round_key */
    ariaXOR(state, key->rd_key[key->rounds], state);

    out = state;
}

void Aria_decrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key){
    Aria_encrypt(in, out, key);
}
