/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria primitive
**********************************************/

#ifndef HEADER_ARIA_H
#define HEADER_ARIA_H

#include <openssl/opensslconf.h>

#ifdef OPENSSL_NO_ARIA
#error ARIA is disabled.
#endif

#include <stddef.h>

#define ARIA_ENCRYPT	1
#define ARIA_DECRYPT	0

#define ARIA_BLOCK_SIZE 16
#define ARIA_MAX_ROUND 17

struct aria_key_st {
  u8 rd_key[ARIA_MAX_ROUND][ARIA_BLOCK_SIZE];
  u8 w[4][ARIA_BLOCK_SIZE];
	int rounds;
};
typedef struct aria_key_st ARIA_KEY;

int ARIA_set_encrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key);
int ARIA_set_decrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key);

void ARIA_encrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key);
void ARIA_decrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key);

#endif /* !HEADER_ARIA_H */
