#include <stdio.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <emmintrin.h>

/* gcc -msse2 -mavx src/aria_asm.c -o aria */
typedef unsigned long long u64;  /* 64 bits variable */

void print128(__m128i value) {
  __ino64_t* v64 = (__ino64_t*)&value;
  printf("%.16llx %.16llx\n", (u64)v64[1], (u64)v64[0]);
}

void print256(__m256i value) {
  __ino64_t* v64 = (__ino64_t*)&value;
  printf("%.16llx %.16llx %.16llx %.16llx\n", (u64)v64[3], (u64)v64[2],
        (u64)v64[1], (u64)v64[0]);
}

/* left circle rotation on 128bits for count bits */
__m128i _mm_cshiftl(__m128i input, unsigned char count){
  __m128i low = _mm_bslli_si128(input, 8);
  __m128i high = _mm_bsrli_si128(input, 8);
  low = _mm_srli_epi64(low, 64-count);
  high = _mm_srli_epi64(high, 64-count);
  input = _mm_slli_epi64(input, count);
  input = _mm_or_si128(input, low);
  return _mm_or_si128(input, high);
}

/* right circle rotation on 128bits for count bits */
__m128i _mm_cshiftr(__m128i input, unsigned char count){
  __m128i high = _mm_bslli_si128(input, 8);
  __m128i low = _mm_bsrli_si128(input, 8);
  high = _mm_slli_epi64(high, 64-count);
  low = _mm_slli_epi64(low, 64-count);
  input = _mm_srli_epi64(input, count);
  input = _mm_or_si128(input, low);
  return _mm_or_si128(input, high);
}

int main() {
  __m256i key = _mm256_setzero_si256();
  __m128i a = _mm_set_epi32(0x2afbea74, 0x1e1746dd, 0x55c63ba1, 0xafcea0a5);
  __m128i b = _mm_set_epi32(0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f);
  __m128i d = _mm_xor_si128(b, _mm_cshiftr(a, 19));
  print256(key);
  return 0;
}