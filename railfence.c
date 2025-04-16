#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000

// Encryption
void encryptMessage(const char *plaintext, int rails, char *ciphertext) {
    int len = strlen(plaintext);
    char rail[rails][len];

    // Initialize matrix with newlines
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    int row = 0, col = 0;
    int dir_down = 0;

    for (int i = 0; i < len; i++) {
        // Change direction if we hit top or bottom rail
        if (row == 0 || row == rails - 1)
            dir_down = !dir_down;

        rail[row][col++] = plaintext[i];

        row += dir_down ? 1 : -1;
    }

    int k = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] != '\n')
                ciphertext[k++] = rail[i][j];
        }
    }
    ciphertext[k] = '\0';
}

// Decryption
void decryptMessage(const char *ciphertext, int rails, char *plaintext) {
    int len = strlen(ciphertext);
    char rail[rails][len];

    // Initialize matrix with newlines
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    // Mark positions with '*'
    int row = 0, col = 0;
    int dir_down = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0 || row == rails - 1)
            dir_down = !dir_down;

        rail[row][col++] = '*';
        row += dir_down ? 1 : -1;
    }

    // Fill the marked positions with ciphertext
    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] == '*' && index < len) {
                rail[i][j] = ciphertext[index++];
            }
        }
    }

    // Read the plaintext by zig-zag
    row = 0, col = 0;
    dir_down = 0;
    int k = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0 || row == rails - 1)
            dir_down = !dir_down;

        if (rail[row][col] != '\n')
            plaintext[k++] = rail[row][col++];
        row += dir_down ? 1 : -1;
    }
    plaintext[k] = '\0';
}

int main() {
    char choice;
    int rails;
    char input[MAX_LEN];
    char output[MAX_LEN];

    printf("Enter E for encryption or D for decryption: ");
    scanf(" %c", &choice);

    printf("Enter the number of rails: ");
    scanf("%d", &rails);

    if (choice == 'E' || choice == 'e') {
        printf("Enter plaintext (no spaces): ");
        scanf("%s", input);
        encryptMessage(input, rails, output);
        printf("Encrypted Message: %s\n", output);
    } else if (choice == 'D' || choice == 'd') {
        printf("Enter ciphertext (no spaces): ");
        scanf("%s", input);
        decryptMessage(input, rails, output);
        printf("Decrypted Message: %s\n", output);
    } else {
        printf("Invalid choice. Please enter E or D.\n");
    }

    return 0;
}
