/***********************************************************************
* FILENAME :        aria_ecb.c
*
* DESCRIPTION :
*       Function to perform ecb encrypt/decrypt
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

void
Aria_ecb_encrypt(const unsigned char *in, unsigned char *out,
    const ARIA_KEY *key, const int enc)
{
    if (ARIA_ENCRYPT == enc)
        Aria_encrypt(in, out, key);
    else
        Aria_decrypt(in, out, key);
}
