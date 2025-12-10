#include <stdio.h>
#include <time.h>

#define BLOCK_SIZE 8
#define HALF_SIZE (BLOCK_SIZE / 2)

// ============================
//   FUNCTION PROTOTYPES
// ============================

void split(char msg[], char L[], char R[]);
int xor_op(int a, int b);
int rand_keygen();
unsigned char F(unsigned char r, unsigned char k);



// ============================
//   MAIN
// ============================

int main()
{
    char msg[BLOCK_SIZE + 1];  // +1 for null terminator
    char L[HALF_SIZE];
    char R[HALF_SIZE];

    printf("Enter an 8-character message:\n");
    fgets(msg, BLOCK_SIZE + 1, stdin);

    // --- SPLIT TEST ---
    split(msg, L, R);

    printf("\nLeft half:  ");
    for (int i = 0; i < HALF_SIZE; i++) {
        printf("%c", L[i]);
    }

    printf("\nRight half: ");
    for (int i = 0; i < HALF_SIZE; i++) {
        printf("%c", R[i]);
    }
    printf("\n");

    // --- XOR TEST ---
    int x = 1;
    int y = 0;
    printf("\nXOR test: %d ^ %d = %d\n", x, y, xor_op(x, y));

    // --- RANDOM KEY TEST ---
    unsigned char key = rand_keygen();
    printf("Random key generated: %d\n", key);

    // --- FEISTEL ROUND FUNCTION F TEST ---
    unsigned char test_r = R[0];     // first byte of right half
    unsigned char f_out = F(test_r, key);

    printf("\nF Test:");
    printf("\nR[0] = %d", test_r);
    printf("\nKey  = %d", key);
    printf("\nF(R, K) = %d\n", f_out);

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
    srand(time(NULL));
    return rand() % 256;     // return 1-byte key
}



// ============================
//   FEISTEL ROUND FUNCTION F
// ============================

unsigned char F(unsigned char r, unsigned char k)
{
    return r ^ k;   // simple Feistel round function (toy version)
}
