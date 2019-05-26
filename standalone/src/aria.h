#ifndef HEADER_ARIA_H
#define HEADER_ARIA_H

#define ARIA_ENCRYPT 1
#define ARIA_DECRYPT 0

int Aria_set_key(const unsigned char *in, const int size, ARIA_KEY *key);

#endif /* HEADER_ARIA_H */