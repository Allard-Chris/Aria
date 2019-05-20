#ifndef HEADER_ARIA_H
#define HEADER_ARIA_H

#include <openssl/opensslconf.h>

#ifdef OPENSSL_NO_ARIA
#error ARIA is disabled.
#endif

#include <stddef.h>

#define ARIA_ENCRYPT	1
#define ARIA_DECRYPT	0

struct aria_key_st {
	int grand_rounds;
};
typedef struct aria_key_st ARIA_KEY;

void Aria_encrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key);
void Aria_decrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key);
int Aria_set_encrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key);
int Aria_set_decrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key);

void Aria_ecb_encrypt(const unsigned char *in, unsigned char *out,
	const ARIA_KEY *key, const int enc);

void Aria_cbc_encrypt(const unsigned char *in, unsigned char *out,
	size_t length, const ARIA_KEY *key,
	unsigned char *ivec, const int enc);

#endif /* !HEADER_Aria_H */