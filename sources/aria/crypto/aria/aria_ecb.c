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
