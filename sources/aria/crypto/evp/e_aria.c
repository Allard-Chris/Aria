/* ARIA subkey Structure */
#include <string.h>

#include <openssl/opensslconf.h>

#ifndef OPENSSL_NO_ARIA
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aria.h>
#include "evp_locl.h"

static int Aria_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc);

typedef struct {
    ARIA_KEY ks;
} EVP_ARIA_KEY;

static int aria_128_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out, const unsigned char *in, size_t inl){
//	while(inl>=EVP_MAXCHUNK) {
//	    Aria_cbc_encrypt(in, out, (long)EVP_MAXCHUNK, &((EVP_ARIA_KEY *)ctx->cipher_data)->ks, ctx->iv, ctx->encrypt);
//	    inl-=EVP_MAXCHUNK;
//	    in +=EVP_MAXCHUNK;
//	    out+=EVP_MAXCHUNK;
//	}
//	if (inl)
//	    Aria_cbc_encrypt(in, out, (long)inl, &((EVP_ARIA_KEY *)ctx->cipher_data)->ks, ctx->iv, ctx->encrypt);
	return 1;
}

static int aria_192_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out, const unsigned char *in, size_t inl){
//	while(inl>=EVP_MAXCHUNK) {
//	    Aria_cbc_encrypt(in, out, (long)EVP_MAXCHUNK, &((EVP_ARIA_KEY *)ctx->cipher_data)->ks, ctx->iv, ctx->encrypt);
//	    inl-=EVP_MAXCHUNK;
//	    in +=EVP_MAXCHUNK;
//	    out+=EVP_MAXCHUNK;
//	}
//	if (inl)
//	    Aria_cbc_encrypt(in, out, (long)inl, &((EVP_ARIA_KEY *)ctx->cipher_data)->ks, ctx->iv, ctx->encrypt);
	return 1;
}

static int aria_256_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out, const unsigned char *in, size_t inl){
//	while(inl>=EVP_MAXCHUNK) {
//	    Aria_cbc_encrypt(in, out, (long)EVP_MAXCHUNK, &((EVP_ARIA_KEY *)ctx->cipher_data)->ks, ctx->iv, ctx->encrypt);
//	    inl-=EVP_MAXCHUNK;
//	    in +=EVP_MAXCHUNK;
//	    out+=EVP_MAXCHUNK;
//	}
//	if (inl)
//	    Aria_cbc_encrypt(in, out, (long)inl, &((EVP_ARIA_KEY *)ctx->cipher_data)->ks, ctx->iv, ctx->encrypt);
	return 1;
}

static int aria_128_ecb_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out, const unsigned char *in, size_t inl) {
//	size_t i, bl;
//	bl = ctx->cipher->block_size;
//	if(inl < bl) return 1;
//	inl -= bl;
//	for(i=0; i <= inl; i+=bl)
//		Aria_ecb_encrypt(in + i, out + i, &((EVP_ARIA_KEY *)ctx->cipher_data)->ks, ctx->encrypt);
	return 1;
}

static int aria_192_ecb_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out, const unsigned char *in, size_t inl) {
//	size_t i, bl;
//	bl = ctx->cipher->block_size;
//	if(inl < bl) return 1;
//	inl -= bl;
//	for(i=0; i <= inl; i+=bl)
//		Aria_ecb_encrypt(in + i, out + i, &((EVP_ARIA_KEY *)ctx->cipher_data)->ks, ctx->encrypt);
	return 1;
}

static int aria_256_ecb_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out, const unsigned char *in, size_t inl) {
//	size_t i, bl;
//	bl = ctx->cipher->block_size;
//	if(inl < bl) return 1;
//	inl -= bl;
//	for(i=0; i <= inl; i+=bl)
//		Aria_ecb_encrypt(in + i, out + i, &((EVP_ARIA_KEY *)ctx->cipher_data)->ks, ctx->encrypt);
	return 1;
}

static const EVP_CIPHER aria_128_cbc = {
//	.nid = NID_aria_128_cbc, 
//    .block_size = 16,
//    .key_len = 16, 
//    .iv_len = 16, 
//	.flags = EVP_CIPH_CBC_MODE,
//	.init = Aria_init_key,
//	.do_cipher = aria_128_cbc_cipher,
//	.ctx_size = sizeof(EVP_ARIA_KEY)
};
const EVP_CIPHER *EVP_aria_128_cbc(void) { return &aria_128_cbc; }

static const EVP_CIPHER aria_128_ecb = {
//	.nid = NID_aria_128_ecb, 
//    .block_size = 16,
//    .key_len = 16, 
//    .iv_len = 16, 
//	.flags = EVP_CIPH_ECB_MODE,
//	.init = Aria_init_key,
//	.do_cipher = aria_128_ecb_cipher,
//	.ctx_size = sizeof(EVP_ARIA_KEY)
};
const EVP_CIPHER *EVP_aria_128_ecb(void) { return &aria_128_ecb; }

static const EVP_CIPHER aria_192_cbc = {
//	.nid = NID_aria_192_cbc, 
//    .block_size = 16,
//    .key_len = 24, 
//    .iv_len = 16, 
//	.flags = EVP_CIPH_CBC_MODE,
//	.init = Aria_init_key,
//	.do_cipher = aria_192_cbc_cipher,
//	.ctx_size = sizeof(EVP_ARIA_KEY)
};
const EVP_CIPHER *EVP_aria_192_cbc(void) { return &aria_192_cbc; }

static const EVP_CIPHER aria_192_ecb = {
//	.nid = NID_aria_192_ecb, 
//    .block_size = 16,
//    .key_len = 24, 
//    .iv_len = 16, 
//	.flags = EVP_CIPH_ECB_MODE,
//	.init = Aria_init_key,
//	.do_cipher = aria_192_ecb_cipher,
//	.ctx_size = sizeof(EVP_ARIA_KEY)
};
const EVP_CIPHER *EVP_aria_192_ecb(void) { return &aria_192_ecb; }

static const EVP_CIPHER aria_256_cbc = {
//	.nid = NID_aria_256_cbc, 
//    .block_size = 16,
//    .key_len = 32, 
//    .iv_len = 16, 
//	.flags = EVP_CIPH_CBC_MODE,
//	.init = Aria_init_key,
//	.do_cipher = aria_256_cbc_cipher,
//	.ctx_size = sizeof(EVP_ARIA_KEY)
};
const EVP_CIPHER *EVP_aria_256_cbc(void) { return &aria_256_cbc; }

static const EVP_CIPHER aria_256_ecb = {
//	.nid = NID_aria_256_ecb, 
//    .block_size = 16,
//    .key_len = 32, 
//    .iv_len = 16, 
//	.flags = EVP_CIPH_ECB_MODE,
//	.init = Aria_init_key,
//	.do_cipher = aria_256_ecb_cipher,
//	.ctx_size = sizeof(EVP_ARIA_KEY)
};
const EVP_CIPHER *EVP_aria_256_ecb(void) { return &aria_256_ecb; }

static int
Aria_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc)
{
//    int ret;
//
//    ret = Aria_set_key(key, ctx->key_len * 8, ctx->cipher_data);
//
//    if (ret < 0) {
//        EVPerror(EVP_R_ARIA_KEY_SETUP_FAILED);
//        fprintf(stdout, "HOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
//        return 0;
//    }

    return 1;
}
#endif