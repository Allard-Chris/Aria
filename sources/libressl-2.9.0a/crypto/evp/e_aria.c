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

/* ARIA 128 CBC */

static int aria_128_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t len){
        return 0;
}

static const EVP_CIPHER aria_128_cbc = {
    .nid = NID_aria_128_cbc,
    .block_size = 16,
    .key_len = 16,
    .iv_len = 16,
    .flags = EVP_CIPH_CBC_MODE,
    .init = aria_init_key,
    .do_cipher = aria_128_cbc_cipher,
    .ctx_size = sizeof(EVP_ARIA_KEY)
};

const EVP_CIPHER *EVP_aria_128_cbc(void) { return &aria_128_cbc; }

/* ARIA 128 ECB */

static int aria_128_ecb_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t len){
        return 0;
}

static const EVP_CIPHER aria_128_ecb = {
    .nid = NID_aria_128_ecb,
    .block_size = 16,
    .key_len = 16,
    .iv_len = 16,
    .flags = EVP_CIPH_CBC_MODE,
    .init = aria_init_key,
    .do_cipher = aria_128_ecb_cipher,
    .ctx_size = sizeof(EVP_ARIA_KEY)
};

const EVP_CIPHER *EVP_aria_128_ecb(void) { return &aria_128_ecb; }

/* ARIA 192 CBC */

static int aria_192_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t len){
        return 0;
}

static const EVP_CIPHER aria_192_cbc = {
    .nid = NID_aria_192_cbc,
    .block_size = 16,
    .key_len = 24,
    .iv_len = 16,
    .flags = EVP_CIPH_CBC_MODE,
    .init = aria_init_key,
    .do_cipher = aria_192_cbc_cipher,
    .ctx_size = sizeof(EVP_ARIA_KEY)
};

const EVP_CIPHER *EVP_aria_192_cbc(void) { return &aria_192_cbc; }

/* ARIA 192 ECB */

static int aria_192_ecb_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t len){
        return 0;
}

static const EVP_CIPHER aria_192_ecb = {
    .nid = NID_aria_192_ecb,
    .block_size = 16,
    .key_len = 24,
    .iv_len = 16,
    .flags = EVP_CIPH_CBC_MODE,
    .init = aria_init_key,
    .do_cipher = aria_192_ecb_cipher,
    .ctx_size = sizeof(EVP_ARIA_KEY)
};

const EVP_CIPHER *EVP_aria_192_ecb(void) { return &aria_192_ecb; }

/* ARIA 256 CBC */

static int aria_256_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t len){
        return 0;
}

static const EVP_CIPHER aria_256_cbc = {
    .nid = NID_aria_256_cbc,
    .block_size = 16,
    .key_len = 32,
    .iv_len = 16,
    .flags = EVP_CIPH_CBC_MODE,
    .init = aria_init_key,
    .do_cipher = aria_256_cbc_cipher,
    .ctx_size = sizeof(EVP_ARIA_KEY)
};

const EVP_CIPHER *EVP_aria_256_cbc(void) { return &aria_256_cbc; }

/* ARIA 256 ECB */

static int aria_256_ecb_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t len){
        return 0;
}

static const EVP_CIPHER aria_256_ecb = {
    .nid = NID_aria_256_ecb,
    .block_size = 16,
    .key_len = 32,
    .iv_len = 16,
    .flags = EVP_CIPH_CBC_MODE,
    .init = aria_init_key,
    .do_cipher = aria_256_ecb_cipher,
    .ctx_size = sizeof(EVP_ARIA_KEY)
};

const EVP_CIPHER *EVP_aria_256_ecb(void) { return &aria_256_ecb; }

/* The subkey for Aria is generated. */
static int
aria_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc)
{
    int ret;

    ret = Aria_set_encrypt_key(key, ctx->key_len * 8, ctx->cipher_data);

    if (ret < 0) {
        EVPerror(EVP_R_ARIA_KEY_SETUP_FAILED);
        return 0;
    }

    return 1;
}
#endif