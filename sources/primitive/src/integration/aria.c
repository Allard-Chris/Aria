/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria main functions for libreSSL
**********************************************/
#include <openssl/aria.h>
#include "aria_locl.h"

/* Function for encryption */
void ARIA_encrypt(const unsigned char *in, unsigned char *out, const ARIA_KEY *key) {
	printf("[Aria.c], ARIA_encrypt, in : %s, out : %s, key",in,out);
}

/* Function for decryption */
void ARIA_decrypt(const unsigned char *in, unsigned char *out, const ARIA_KEY *key) {
	printf("[Aria.c], ARIA_decrypt, in : %s, out : %s, key",in,out);
}

/* Set key for encryption */
int ARIA_set_encrypt_key(const unsigned char *userKey, const int bits, ARIA_KEY *key) {
	printf("[Aria.c], ARIA_set_encrypt_key, userKey : %s, nbBits %d, key",userKey,bits);
}

/* Set key for decryption */
int ARIA_set_decrypt_key(const unsigned char *userKey, const int bits, ARIA_KEY *key) {
	printf("[Aria.c], ARIA_set_decrypt_key, userKey : %s, nbBits %d, key",userKey,bits);
}
