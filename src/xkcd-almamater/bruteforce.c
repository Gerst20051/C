#include "skein/skein.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define DEPTH 20
#define RAND 7

u08b_t plaintext[DEPTH+1];

unsigned int low_bits = 1024;
u08b_t hash[1024/8];
Skein1024_Ctxt_t ctx;

u08b_t XOR[1024/8] = {0x5b, 0x4d, 0xa9, 0x5f, 0x5f, 0xa0, 0x82, 0x80, 0xfc, 0x98, 0x79, 0xdf, 0x44, 0xf4, 0x18, 0xc8, 0xf9, 0xf1, 0x2b, 0xa4, 0x24, 0xb7, 0x75, 0x7d, 0xe0, 0x2b, 0xbd, 0xfb, 0xae, 0x0d, 0x4c, 0x4f, 0xdf, 0x93, 0x17, 0xc8, 0x0c, 0xc5, 0xfe, 0x04, 0xc6, 0x42, 0x90, 0x73, 0x46, 0x6c, 0xf2, 0x97, 0x06, 0xb8, 0xc2, 0x59, 0x99, 0xdd, 0xd2, 0xf6, 0x54, 0x0d, 0x44, 0x75, 0xcc, 0x97, 0x7b, 0x87, 0xf4, 0x75, 0x7b, 0xe0, 0x23, 0xf1, 0x9b, 0x8f, 0x40, 0x35, 0xd7, 0x72, 0x28, 0x86, 0xb7, 0x88, 0x69, 0x82, 0x6d, 0xe9, 0x16, 0xa7, 0x9c, 0xf9, 0xc9, 0x4c, 0xc7, 0x9c, 0xd4, 0x34, 0x7d, 0x24, 0xb5, 0x67, 0xaa, 0x3e, 0x23, 0x90, 0xa5, 0x73, 0xa3, 0x73, 0xa4, 0x8a, 0x5e, 0x67, 0x66, 0x40, 0xc7, 0x9c, 0xc7, 0x01, 0x97, 0xe1, 0xc5, 0xe7, 0xf9, 0x02, 0xfb, 0x53, 0xca, 0x18, 0x58, 0xb6};

unsigned long long count = 0;

static inline void checkHash() {
	assert(Skein1024_Init(&ctx, 1024) == SKEIN_SUCCESS);
	assert(Skein1024_Update(&ctx, plaintext, DEPTH) == SKEIN_SUCCESS);
	assert(Skein1024_Final(&ctx, hash) == SKEIN_SUCCESS);
	unsigned int bits_one = 0;
	for (unsigned int i = 0; i < 1024/8; i++) {
		u08b_t bits = hash[i] ^ XOR[i];
		for (unsigned char j = 0; j < 8; j++)
			bits_one += (bits >> j) & 1;
	}
	if (bits_one < low_bits) {
		low_bits = bits_one;
		fprintf(stdout, "New best: \"%s\" %d\n", plaintext, bits_one);
		fflush(stdout);
	}
//	count++; if (count > 10000000) exit(0);
}

void recursiveSolve(int depth) {
	if (depth == 0) {
		for (unsigned char i = 'a'; i <= 'z'; i++) {
			plaintext[depth] = (u08b_t)i;
			checkHash();
		}
		for (unsigned char i = '0'; i <= '9'; i++) {
			plaintext[depth] = (u08b_t)i;
			checkHash();
		}
		for (unsigned char i = 'A'; i <= 'Z'; i++) {
			plaintext[depth] = (u08b_t)i;
			checkHash();
		}
	} else {
		for (unsigned char i = 'a'; i <= 'z'; i++) {
			plaintext[depth] = (u08b_t)i;
			recursiveSolve(depth-1);
		}
		for (unsigned char i = '0'; i <= '9'; i++) {
			plaintext[depth] = (u08b_t)i;
			recursiveSolve(depth-1);
		}
		for (unsigned char i = 'A'; i <= 'Z'; i++) {
			plaintext[depth] = (u08b_t)i;
			recursiveSolve(depth-1);
		}
	}
}

int main(int argc, char** argv) {
	memset(plaintext, 0, sizeof(plaintext));

	srand(time(NULL));
	// Poor man's alphanumeric random generator
	for (unsigned int i = RAND; i < DEPTH; i++) {
		while (!((plaintext[i] <= 'z' && plaintext[i] >= 'a') || (plaintext[i] >= 'A' && plaintext[i] <= 'Z') || (plaintext[i] >= '0' && plaintext[i] <= '9')))
			plaintext[i] = rand();
	}

	recursiveSolve(DEPTH-RAND);
}
