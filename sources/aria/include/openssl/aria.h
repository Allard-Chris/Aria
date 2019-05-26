/***********************************************************************
* FILENAME :        aria.h
*
* DESCRIPTION :
*       All main functions for decrypt/encrypt header
*
*
* NOTES :
*        Copy from crypto/aria/aria.h
*
*
*
* AUTHOR :    Allard Chris & Aulagnier Corentin
* START DATE :  02-2019
*
* Version : 0.1
*
*
***********************************************************************/
#ifndef HEADER_ARIA_H
#define HEADER_ARIA_H

#include <openssl/opensslconf.h>

#ifdef OPENSSL_NO_ARIA
#error ARIA is disabled.
#endif

#include <stddef.h>

#define ARIA_ENCRYPT    1
#define ARIA_DECRYPT    0
#define ARIA_BLOCK_SIZE 16
#define ARIA_MAX_ROUND  17

struct aria_key_st {
    unsigned char rd_key[ARIA_MAX_ROUND][ARIA_BLOCK_SIZE];
    unsigned char ck[3][ARIA_BLOCK_SIZE];
    unsigned char wk[4][ARIA_BLOCK_SIZE];
    int rounds;
};
typedef struct aria_key_st ARIA_KEY;

void Aria_encrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key);
void Aria_decrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key);
int Aria_set_encrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key);
int Aria_set_decrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key);
void Aria_ecb_encrypt(const unsigned char *in, unsigned char *out,
	const ARIA_KEY *key, const int enc);

void Aria_cbc_encrypt(const unsigned char *in, unsigned char *out,
	size_t length, const ARIA_KEY *key,
	unsigned char *ivec, const int enc);

#endif /* !HEADER_Aria_H */