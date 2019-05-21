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

IMPLEMENT_BLOCK_CIPHER_BASIC(
    aria_128, /* cname */
    ks, /* ksched */
    Aria, /* cprefix */
    EVP_ARIA_KEY, /* kstruct */
    NID_aria_128, /* nid */
    16, /* block_size */
    16, /* key_len */
    16, /* iv_len */
    128, /* cbits */
    0, /* flags */
    Aria_init_key, /* init_key */
    NULL, /* cleanup */
    EVP_CIPHER_set_asn1_iv, /* set_asn1 */
    EVP_CIPHER_get_asn1_iv, /* get_asn1 */
    NULL /* ctrl */)
/* The subkey for Aria is generated. */

IMPLEMENT_BLOCK_CIPHER_BASIC(
    aria_192, /* cname */
    ks, /* ksched */
    Aria, /* cprefix */
    EVP_ARIA_KEY, /* kstruct */
    NID_aria_192, /* nid */
    16, /* block_size */
    24, /* key_len */
    16, /* iv_len */
    128, /* cbits */
    0, /* flags */
    Aria_init_key, /* init_key */
    NULL, /* cleanup */
    EVP_CIPHER_set_asn1_iv, /* set_asn1 */
    EVP_CIPHER_get_asn1_iv, /* get_asn1 */
    NULL /* ctrl */)
/* The subkey for Aria is generated. */

IMPLEMENT_BLOCK_CIPHER_BASIC(
    aria_256, /* cname */
    ks, /* ksched */
    Aria, /* cprefix */
    EVP_ARIA_KEY, /* kstruct */
    NID_aria_256, /* nid */
    16, /* block_size */
    32, /* key_len */
    16, /* iv_len */
    128, /* cbits */
    0, /* flags */
    Aria_init_key, /* init_key */
    NULL, /* cleanup */
    EVP_CIPHER_set_asn1_iv, /* set_asn1 */
    EVP_CIPHER_get_asn1_iv, /* get_asn1 */
    NULL /* ctrl */)
/* The subkey for Aria is generated. */

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