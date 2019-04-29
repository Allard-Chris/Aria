#include <string.h>

#include <openssl/opensslconf.h>

#ifndef OPENSSL_NO_ARIA
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aria.h>
#include "evp_locl.h"

/* ARIA subkey Structure */
typedef struct {
    ARIA_KEY ks;
} EVP_ARIA_KEY;

static int aria_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
                         const unsigned char *iv, int enc)
{
   int ret;
   int mode = EVP_CIPHER_CTX_mode(ctx);
   if (mode==EVP_CIPH_CFB_MODE||mode==EVP_CIPH_OFB_MODE||enc)
       ret = ARIA_set_encrypt_key(key, EVP_CIPHER_CTX_key_length(ctx) * 8,
                                  EVP_CIPHER_CTX_get_cipher_data(ctx));
   else
       ret = ARIA_set_decrypt_key(key, EVP_CIPHER_CTX_key_length(ctx) * 8,
                                  EVP_CIPHER_CTX_get_cipher_data(ctx));
   if(ret < 0) {
       EVPerr(EVP_F_ARIA_INIT_KEY,EVP_R_ARIA_KEY_SETUP_FAILED);
       return 0;
   }
   return 1; 
}

static void aria_cbc_encrypt(const unsigned char *in, unsigned char *out,
                             size_t len, const ARIA_KEY *key,
                             unsigned char *ivec, const int enc)
{
   if (enc)
       CRYPTO_cbc128_encrypt(in, out, len, key, ivec,
                             (block128_f) aria_encrypt);
   else
       CRYPTO_cbc128_decrypt(in, out, len, key, ivec,
                             (block128_f) aria_encrypt);
}



