#include "openssl/aria.h"

void Aria_encrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key) {
                      return NULL;
}
void Aria_decrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key){
                      return NULL;
}
int Aria_set_encrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key){
                             return 0;
                         }
int Aria_set_decrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key){
                             return 0;
                         }
