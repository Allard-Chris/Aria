/* ARIA subkey Structure */
#include <openssl/opensslconf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aria.h>
#include "evp_locl.h"

static int aria_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc);

typedef struct {
    ARIA_KEY ks;
} EVP_ARIA_KEY;

IMPLEMENT_BLOCK_CIPHER(
    aria_128, /* cname */
    ks, /* ksched */
    Aria, /* cprefix */
    EVP_ARIA_KEY, /* kstruct */
    NID_aria_128, /* NID */
    16, /* block_size */
    16, /* key_len */
    16, /* iv_len */
    128, /* cbits */
    0, /* flags */
    aria_init_key, /* init_key */
    NULL, /* cleanup */
    EVP_CIPHER_set_asn1_iv, /* set_asn1 */
    EVP_CIPHER_get_asn1_iv, /* get_asn1 */
    NULL /* ctrl */
)
IMPLEMENT_BLOCK_CIPHER(aria_192, ks, Aria, EVP_ARIA_KEY,
    NID_aria_128, 16, 24, 16, 192,
    0, aria_init_key, NULL,
    EVP_CIPHER_set_asn1_iv,
    EVP_CIPHER_get_asn1_iv,
    NULL)
IMPLEMENT_BLOCK_CIPHER(aria_256, ks, Aria, EVP_ARIA_KEY,
    NID_aria_128, 16, 32, 16, 256,
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

	ret = Aria_set_key(key, ctx->key_len * 8, ctx->cipher_data);

	if (ret < 0) {
		EVPerror(EVP_R_ARIA_KEY_SETUP_FAILED);
		return 0;
	}

	return 1;
}
#endif