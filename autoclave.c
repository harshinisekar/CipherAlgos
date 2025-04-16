#include <stdio.h>
#include <string.h>
#include <ctype.h>

void sanitizeInput(char* text) {
    int len = strlen(text);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            text[j++] = toupper(text[i]);
        }
    }
    text[j] = '\0';
}

void encryptAutoclave(char* plaintext, char* key, char* ciphertext) {
    sanitizeInput(plaintext);
    sanitizeInput(key);

    int len = strlen(plaintext);
    char extendedKey[len + 1];

    // Extend the key to match the length of the plaintext
    int keyLen = strlen(key);
    for (int i = 0; i < len; i++) {
        extendedKey[i] = key[i % keyLen];
    }
    extendedKey[len] = '\0';

    // Encrypt using Autoclave cipher logic
    for (int i = 0; i < len; i++) {
        char p = plaintext[i];
        char k = extendedKey[i];
        ciphertext[i] = ((p - 'A') + (k - 'A')) % 26 + 'A';
    }
    ciphertext[len] = '\0'; // Null-terminate the ciphertext
}

void decryptAutoclave(char* ciphertext, char* key, char* plaintext) {
    sanitizeInput(ciphertext);
    sanitizeInput(key);

    int len = strlen(ciphertext);
    char extendedKey[len + 1];

    // Decrypt using Autoclave cipher logic
    for (int i = 0; i < len; i++) {
        char k;
        if (i < strlen(key)) {
            k = key[i];
        } else {
            k = plaintext[i - strlen(key)];
        }
        char c = ciphertext[i];
        plaintext[i] = ((c - k + 26) % 26) + 'A';
    }
    plaintext[len] = '\0'; 
}

int main() {
    char text[1000], key[1000], result[1000];
    int choice;

    printf("Autoclave Cipher\n");
    printf("1. Encrypt\n2. Decrypt\nEnter choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Enter plaintext: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = '\0'; // Remove the newline character from the input

        printf("Enter key: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0'; // Remove the newline character from the input

        encryptAutoclave(text, key, result);
        printf("Encrypted Text: %s\n", result);
    } else if (choice == 2) {
        printf("Enter ciphertext: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = '\0'; // Remove the newline character from the input

        printf("Enter key: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0'; // Remove the newline character from the input

        decryptAutoclave(text, key, result);
        printf("Decrypted Text: %s\n", result);
    } else {
        printf("Invalid option!\n");
    }

    return 0;
}
