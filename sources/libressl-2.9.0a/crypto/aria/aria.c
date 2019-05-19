#include "openssl/aria.h"

void ARIA_encrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key)
void ARIA_decrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key)
int ARIA_set_encrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key)
int ARIA_set_decrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key)
