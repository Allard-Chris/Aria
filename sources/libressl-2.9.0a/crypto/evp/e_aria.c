/* ARIA subkey Structure */
#include <string.h>

#include <openssl/opensslconf.h>

#ifndef OPENSSL_NO_ARIA
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aria.h>
#include "evp_locl.h"

static int Aria_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc);

typedef struct {
    ARIA_KEY ks;
} EVP_ARIA_KEY;

#define data(ctx)	EVP_C_DATA(EVP_ARIA_KEY,ctx)

BLOCK_CIPHER_def_cbc(aria_128, EVP_ARIA_KEY, NID_aria_128, 16, 16, 16, 0, Aria_init_key, NULL, EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv, NULL)
BLOCK_CIPHER_def_cbc(aria_128, EVP_ARIA_KEY, NID_aria_192, 16, 24, 16, 0, Aria_init_key, NULL, EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv, NULL)
BLOCK_CIPHER_def_cbc(aria_128, EVP_ARIA_KEY, NID_aria_256, 16, 32, 16, 0, Aria_init_key, NULL, EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv, NULL)

BLOCK_CIPHER_def_ecb(aria_128, EVP_ARIA_KEY, NID_aria_128, 16, 16, 0, Aria_init_key, NULL, EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv, NULL)
BLOCK_CIPHER_def_ecb(aria_128, EVP_ARIA_KEY, NID_aria_128, 16, 24, 0, Aria_init_key, NULL, EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv, NULL)
BLOCK_CIPHER_def_ecb(aria_128, EVP_ARIA_KEY, NID_aria_128, 16, 32, 0, Aria_init_key, NULL, EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv, NULL)

BLOCK_CIPHER_func_cbc(aria_128, Aria, EVP_ARIA_KEY, ks)
BLOCK_CIPHER_func_ecb(aria_128, Aria, EVP_ARIA_KEY, ks)

static int
Aria_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc)
{
    int ret;

    ret = Aria_set_encrypt_key(key, ctx->key_len * 8, ctx->cipher_data);

    if (ret < 0) {
        EVPerror(EVP_R_ARIA_KEY_SETUP_FAILED);
        fprintf(stdout, "HOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
        return 0;
    }

    return 1;
}
#endif