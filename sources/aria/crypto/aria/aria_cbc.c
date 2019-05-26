/***********************************************************************
* FILENAME :        aria_cbc.c
*
* DESCRIPTION :
*       Function to perform cbc encrypt/decrypt
*
*
* NOTES :
*       Based on camellia cipher
*
*
* AUTHOR :    Allard Chris & Aulagnier Corentin
* START DATE :  02-2019
*
* Version : 0.1
*
*
***********************************************************************/
#include <openssl/aria.h>
#include <openssl/modes.h>

void
Aria_cbc_encrypt(const unsigned char *in, unsigned char *out, size_t len,
    const ARIA_KEY *key, unsigned char *ivec, const int enc)
{
    if (enc)
        CRYPTO_cbc128_encrypt(in, out, len, key, ivec,
            (block128_f)Aria_encrypt);
    else
        CRYPTO_cbc128_decrypt(in, out, len, key, ivec,
           (block128_f)Aria_decrypt);
}
