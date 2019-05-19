/* ARIA subkey Structure */
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aria.h>
#include "evp_locl.h"

typedef struct {
    ARIA_KEY ks;
} EVP_ARIA_KEY;

static const EVP_CIPHER r4_cipher = {
   NID_rc4,
   1, EVP_RC4_KEY_SIZE, 0,
   EVP_CIPH_VARIABLE_LENGTH,
   rc4_init_key,
   rc4_cipher,
   NULL,
   sizeof(EVP_RC4_KEY),
   NULL,
   NULL,
   NULL,
   NULL
};

const EVP_CIPHER *EVP_rc4(void)
{
   return (&r4_cipher);
}

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

/* EVP_CIPHER struct */
typedef struct {
    MYKEY k;
    union {
        void (*cipher) (MYKEY *k, size_t len, const unsigned char *in,
                        unsigned char *out);
    } stream;
} EVP_MYCIPHER_KEY;

/* Key Initialization Function */
static int mycipher_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
                             const unsigned char *iv, int enc)
{
    enc ? mycipher_enc_set_key(&data(ctx)->k) : 
              mycipher_dec_set_key(&data(ctx)->k);
    data(ctx)->stream.cipher = enc ? encrypt_mycipher : decrypt_mycipher;
    return 1;
}

/* Cipher Initialization Function */
static int mycipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                    const unsigned char *in, size_t inl)
{
    (*data(ctx)->stream.cipher) (&data(ctx)->k, inl, in, out);
    return 1;
}