/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria prototype functions for libreSSL integration
**********************************************/
#ifndef HEADER_ARIA_LOCL_H
#define HEADER_ARIA_LOCL_H

#include <openssl/opensslconf.h>

#ifdef OPENSSL_NO_ARIA
#error ARIA is disabled.
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aria_key_st {
	unsigned int rd_key[4 *(AES_MAXNR + 1)];
	int rounds;
};
typedef struct aria_key_st ARIA_KEY;

/* Function for encryption */
void ARIA_encrypt(const unsigned char *in, unsigned char *out, const ARIA_KEY *key);

/* Function for decryption */
void ARIA_decrypt(const unsigned char *in, unsigned char *out, const ARIA_KEY *key);

/* Set key for encryption */
int ARIA_set_encrypt_key(const unsigned char *userKey, const int bits, ARIA_KEY *key);

/* Set key for decryption */
int ARIA_set_decrypt_key(const unsigned char *userKey, const int bits, ARIA_KEY *key);
