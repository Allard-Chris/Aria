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
#define ODD 0
#define EVEN 1
#define W0 0
#define W1 1
#define W2 2
#define W3 3
#define CK1 0
#define CK2 1
#define CK3 2
#define MAX_SIZE_OCTETS 32
#define CHUNK_16_OCTETS 16

typedef unsigned char      u8;   // 8 bits variable
typedef unsigned short     u16;  // 16 bits variable
typedef unsigned long      u32;  // 32 bits variable
typedef unsigned long long u64;  // 64 bits variable

/* init array with the maximum size of an Aria key */
/* so use correctly "size" attribute to get the key values correctly */
/* must be optimised later */
typedef struct {
  int size;
  u8  key[MAX_SIZE_OCTETS];
} ariaKey_t;

/* structure used to store all data for tests */
typedef struct {
  const u8 key_add[CHUNK_16_OCTETS];
  const u8 s_box[CHUNK_16_OCTETS];
  const u8 diff_layer[CHUNK_16_OCTETS];
} round_t;

/* structure used to store round key */
typedef struct {
  u8 ek[17][CHUNK_16_OCTETS];
  u8 constants_key[3][CHUNK_16_OCTETS];
  u8 expansion_key[4][CHUNK_16_OCTETS];
} round_key_t;

#endif /* ARIA_TYPE */