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
#define KEY_128 0
#define KEY_192 1
#define KEY_256 2

typedef unsigned char      u8;   // 8 bits variable
typedef unsigned short     u16;  // 16 bits variable
typedef unsigned long      u32;  // 32 bits variable
typedef unsigned long long u64;  // 64 bits variable

typedef struct key_value {
  u8                val;
  struct key_value* next;
} key_value_t;

typedef struct {
  char         size;
  key_value_t* key;
} ariaKey_t;

/*
typedef struct {
  u8 w0;
  u8 w1;
  u8 w2;
  u8 w3;
} expansion_key_t;

typedef struct {
  unsigned char    key;
  unsigned char    key_size;
  unsigned char    nb_round;
  expansion_key_t* expansion_struct;
} key_t;

typedef struct {
  char*         message;
  unsigned char current_round;
  key_t*        key_struct;
} state_t;
*/
#endif
