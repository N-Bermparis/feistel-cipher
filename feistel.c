#include <stdio.h>
#include <time.h>

#define BLOCK_SIZE 8
#define HALF_SIZE (BLOCK_SIZE / 2)
#define ROUNDS 4     // ✅ Number of Feistel rounds



// ============================
//   FUNCTION PROTOTYPES
// ============================

void split(char msg[], char L[], char R[]);
int xor_op(int a, int b);
int rand_keygen();
unsigned char F(unsigned char r, unsigned char k);
void feistel_round(char L[], char R[], unsigned char key);



// ============================
//   MAIN
// ============================

int main()
{
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

    // --- FINAL CIPHERTEXT BLOCK ---
    printf("\nFinal Cipher Block:\n");
    printf("Left:  ");
    for (int i = 0; i < HALF_SIZE; i++) printf("%02X ", (unsigned char)L[i]);

    printf("\nRight: ");
    for (int i = 0; i < HALF_SIZE; i++) printf("%02X ", (unsigned char)R[i]);

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
//   RANDOM KEY GENERATOR
// ============================

int rand_keygen()
{
    return rand() % 256;
}



// ============================
//   FEISTEL ROUND FUNCTION F
// ============================

unsigned char F(unsigned char r, unsigned char k)
{
    return r ^ k;
}



// ============================
//   ONE FEISTEL ROUND
// ============================

void feistel_round(char L[], char R[], unsigned char key)
{
    char newR[HALF_SIZE];

    for (int i = 0; i < HALF_SIZE; i++) {
        unsigned char f = F(R[i], key);
        newR[i] = xor_op(L[i], f);
    }

    // Swap
    for (int i = 0; i < HALF_SIZE; i++) {
        L[i] = R[i];
        R[i] = newR[i];
    }
}
