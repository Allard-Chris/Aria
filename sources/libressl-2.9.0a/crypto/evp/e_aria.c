/* ARIA subkey Structure */
#include <string.h>

#include <openssl/opensslconf.h>

#ifndef OPENSSL_NO_ARIA
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aria.h>
#include "evp_locl.h"

static int aria_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc);

typedef struct {
    ARIA_KEY ks;
} EVP_ARIA_KEY;

/* Attribute operation for Aria */
#define data(ctx)	EVP_C_DATA(EVP_ARIA_KEY,ctx)

IMPLEMENT_BLOCK_CIPHER(aria_128, ks, Aria, EVP_ARIA_KEY,
    NID_aria_128, 16, 16, 16, 128,
    0, aria_init_key, NULL,
    EVP_CIPHER_set_asn1_iv,
    EVP_CIPHER_get_asn1_iv,
    NULL)
IMPLEMENT_BLOCK_CIPHER(aria_192, ks, Aria, EVP_ARIA_KEY,
    NID_aria_192, 16, 24, 16, 128,
    0, aria_init_key, NULL,
    EVP_CIPHER_set_asn1_iv,
    EVP_CIPHER_get_asn1_iv,
    NULL)
IMPLEMENT_BLOCK_CIPHER(aria_256, ks, Aria, EVP_ARIA_KEY,
    NID_aria_256, 16, 32, 16, 128,
    0, aria_init_key, NULL,
    EVP_CIPHER_set_asn1_iv,
    EVP_CIPHER_get_asn1_iv,
    NULL)

/* The subkey for Aria is generated. */
static int
aria_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc)
{
	int ret;

	ret = ARIA_set_encrypt_key(key, ctx->key_len * 8, ctx->cipher_data);

	if (ret < 0) {
		EVPerror(EVP_R_ARIA_KEY_SETUP_FAILED);
		return 0;
	}

	return 1;
}
#endif