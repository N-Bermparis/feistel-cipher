#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define BLOCK_SIZE 8
#define HALF_SIZE (BLOCK_SIZE / 2)
#define ROUNDS 4



// ============================
//   FUNCTION PROTOTYPES
// ============================

void split(char msg[], char L[], char R[]);
int xor_op(int a, int b);
unsigned char F(unsigned char r, unsigned char k);
void feistel_round(char L[], char R[], unsigned char key);
unsigned char rand_keygen();



// ============================
//   MAIN
// ============================

int main()
{
    //FIX: Seed RNG ONCE (critical for security)
    srand(time(NULL));

    char msg[BLOCK_SIZE + 1];  
    char L[HALF_SIZE];
    char R[HALF_SIZE];

    printf("Enter an 8-character message:\n");
    fgets(msg, BLOCK_SIZE + 1, stdin);

    // --- SPLIT INITIAL BLOCK ---
    split(msg, L, R);

    printf("\nInitial Left:  ");
    for (int i = 0; i < HALF_SIZE; i++) printf("%c", L[i]);

    printf("\nInitial Right: ");
    for (int i = 0; i < HALF_SIZE; i++) printf("%c", R[i]);
    printf("\n");

    // --- MULTI-ROUND FEISTEL ---
    printf("\n--- FEISTEL ROUNDS ---\n");

    for (int round = 0; round < ROUNDS; round++) {

        unsigned char key = rand_keygen();   // round key
        printf("\nRound %d Key: %d\n", round + 1, key);

        feistel_round(L, R, key);

        printf("After Round %d:\n", round + 1);

        printf("Left:  ");
        for (int i = 0; i < HALF_SIZE; i++) printf("%c", L[i]);

        printf("\nRight: ");
        for (int i = 0; i < HALF_SIZE; i++) printf("%c", R[i]);
        printf("\n");
    }

    // --- FINAL CIPHERTEXT BLOCK (HEX SAFE OUTPUT) ---
    printf("\nFinal Cipher Block (HEX):\n");

    printf("Left:  ");
    for (int i = 0; i < HALF_SIZE; i++)
        printf("%02X ", (unsigned char)L[i]);

    printf("\nRight: ");
    for (int i = 0; i < HALF_SIZE; i++)
        printf("%02X ", (unsigned char)R[i]);

    printf("\n");

    return 0;
}



// ============================
//   SPLIT FUNCTION
// ============================

void split(char msg[], char L[], char R[])
{
    for (int i = 0; i < HALF_SIZE; i++) {
        L[i] = msg[i];
        R[i] = msg[i + HALF_SIZE];
    }
}



// ============================
//   XOR FUNCTION
// ============================

int xor_op(int a, int b)
{
    return a ^ b;
}



// ============================
//   FEISTEL ROUND FUNCTION F
// ============================

unsigned char F(unsigned char r, unsigned char k)
{
    return r ^ k;   // toy round function
}



// ============================
//   ONE FEISTEL ROUND
// ============================

void feistel_round(char L[], char R[], unsigned char key)
{
    char newR[HALF_SIZE];

    for (int i = 0; i < HALF_SIZE; i++) {
        unsigned char f = F((unsigned char)R[i], key);
        newR[i] = (char)xor_op((unsigned char)L[i], f);
    }

    // Swap halves
    for (int i = 0; i < HALF_SIZE; i++) {
        L[i] = R[i];
        R[i] = newR[i];
    }
}



// ============================
//   RANDOM KEY GENERATOR
// ============================

unsigned char rand_keygen()
{
    return (unsigned char)(rand() % 256);
}
