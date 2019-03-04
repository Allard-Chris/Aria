/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Globals types and structures for Aria primitive
**********************************************/
#ifndef ARIA_TYPE
#define ARIA_TYPE

#define DECRYPT 0
#define ENCRYPT 1
#define MAX_KEY_SIZE 256
#define CHUNK_SIZE_OCTET 16

typedef unsigned char      u8;   // 8 bits variable
typedef unsigned short     u16;  // 16 bits variable
typedef unsigned long      u32;  // 32 bits variable
typedef unsigned long long u64;  // 64 bits variable

/* init array with the maximum size of an Aria key */
/* so use correctly "size" attribute to get the key values correctly */
/* must be optimised later */
typedef struct {
  int size;
  u8  key[(MAX_KEY_SIZE / 8)];
} ariaKey_t;

/* Aria algorithm can be considered as a series of operations done to */
/* 128-bit array called state. Initialized with plaintext input and each */
/* operation in each round modifies the state */
typedef struct {
  u8 array[CHUNK_SIZE_OCTET];
} state_t;

/* structure used to store all data for tests */
typedef struct {
  u8* key_add;
  u8* s_box;
  u8* diff_layer;
} round_t;

/* structure used to store factional constant */
typedef struct {
  u64 CK[3][2];
} fractional_t;

/* structure used to store expansion key */
typedef struct {
  u8 w0;
  u8 w1;
  u8 w2;
  u8 w3;
} expansion_key_t;

/* structure used to store round key */
typedef struct {
  u8 EK[16];
} round_key_t;

#endif
