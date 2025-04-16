#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MOD 26
#define SIZE 3

void cleanInput(char *text) {
    int i, j = 0;
    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            text[j++] = toupper(text[i]);
        }
    }
    text[j] = '\0';
}

void multiplyMatrix(int key[SIZE][SIZE], int block[SIZE], int result[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            result[i] += key[i][j] * block[j];
        }
        result[i] %= MOD;
    }
}

int determinant(int matrix[SIZE][SIZE]) {
    int det = matrix[0][0] * (matrix[1][1]*matrix[2][2] - matrix[1][2]*matrix[2][1])
            - matrix[0][1] * (matrix[1][0]*matrix[2][2] - matrix[1][2]*matrix[2][0])
            + matrix[0][2] * (matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0]);
    det = det % MOD;
    if (det < 0) det += MOD;
    return det;
}

int modInverse(int a) {
    a = a % MOD;
    for (int x = 1; x < MOD; x++) {
        if ((a * x) % MOD == 1) return x;
    }
    return -1;
}

void adjoint(int matrix[SIZE][SIZE], int adj[SIZE][SIZE]) {
    int temp[SIZE][SIZE];

    adj[0][0] =  (matrix[1][1]*matrix[2][2] - matrix[1][2]*matrix[2][1]) % MOD;
    adj[0][1] = -(matrix[0][1]*matrix[2][2] - matrix[0][2]*matrix[2][1]) % MOD;
    adj[0][2] =  (matrix[0][1]*matrix[1][2] - matrix[0][2]*matrix[1][1]) % MOD;
    adj[1][0] = -(matrix[1][0]*matrix[2][2] - matrix[1][2]*matrix[2][0]) % MOD;
    adj[1][1] =  (matrix[0][0]*matrix[2][2] - matrix[0][2]*matrix[2][0]) % MOD;
    adj[1][2] = -(matrix[0][0]*matrix[1][2] - matrix[0][2]*matrix[1][0]) % MOD;
    adj[2][0] =  (matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0]) % MOD;
    adj[2][1] = -(matrix[0][0]*matrix[2][1] - matrix[0][1]*matrix[2][0]) % MOD;
    adj[2][2] =  (matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0]) % MOD;

    // transpose and mod
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            adj[i][j] = adj[i][j] % MOD;
            if (adj[i][j] < 0) adj[i][j] += MOD;
        }
}

void inverseMatrix(int matrix[SIZE][SIZE], int inverse[SIZE][SIZE]) {
    int det = determinant(matrix);
    int invDet = modInverse(det);

    if (invDet == -1) {
        printf("Matrix is not invertible modulo 26.\n");
        exit(1);
    }

    int adj[SIZE][SIZE];
    adjoint(matrix, adj);

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            inverse[i][j] = (adj[i][j] * invDet) % MOD;
}

void encryptText(char *plaintext, int key[SIZE][SIZE], char *ciphertext) {
    cleanInput(plaintext);
    int len = strlen(plaintext);
    int padding = SIZE - (len % SIZE);
    if (padding != SIZE) {
        for (int i = 0; i < padding; i++) {
            plaintext[len++] = 'X';
        }
        plaintext[len] = '\0';
    }

    for (int i = 0; i < len; i += SIZE) {
        int block[SIZE], result[SIZE];
        for (int j = 0; j < SIZE; j++)
            block[j] = plaintext[i + j] - 'A';
        multiplyMatrix(key, block, result);
        for (int j = 0; j < SIZE; j++)
            *ciphertext++ = result[j] + 'A';
    }
    *ciphertext = '\0';
}

void decryptText(char *ciphertext, int key[SIZE][SIZE], char *plaintext) {
    int inverse[SIZE][SIZE];
    inverseMatrix(key, inverse);
    encryptText(ciphertext, inverse, plaintext);
}

int main() {
    int key[SIZE][SIZE];
    char input[100], output[100];
    char buffer[10];
    int option;

    printf("HILL CIPHER (3x3)\n");
    printf("1. Encrypt\n2. Decrypt\nEnter your choice: ");
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &option) != 1 || (option != 1 && option != 2)) {
        printf("Invalid option.\n");
        return 1;
    }

    printf("Enter the 3x3 key matrix (row-wise, integers mod 26):\n");
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            scanf("%d", &key[i][j]);

    getchar(); 
    printf("Enter the text (UPPERCASE only): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    if (option == 1) {
        encryptText(input, key, output);
        printf("Encrypted Text: %s\n", output);
    } else {
        decryptText(input, key, output);
        printf("Decrypted Text: %s\n", output);
    }

    return 0;
}
