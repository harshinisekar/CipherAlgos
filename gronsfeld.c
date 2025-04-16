#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateNumericKey(const char* text, const char* key, char* fullKey) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int j = 0;

    for (int i = 0; i < textLen; ++i) {
        if (isalpha(text[i])) {
            fullKey[i] = key[j % keyLen];
            j++;
        } else {
            fullKey[i] = text[i];
        }
    }
    fullKey[textLen] = '\0';
}

int main() {
    char text[1000], key[100], result[1000], fullKey[1000];
    int choice;
    printf("Choose an option:\n");
    printf("1. Encrypt using Gronsfeld Cipher\n");
    printf("2. Decrypt using Gronsfeld Cipher\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    // Validate input
    if (choice != 1 && choice != 2) {
        printf("Invalid choice. Please enter 1 for Encrypt or 2 for Decrypt.\n");
        return 1;
    }
    printf("Enter the message: ");
    getchar();
    fgets(text, sizeof(text), stdin);

    // Remove newline character at the end of the string if present
    size_t len = strlen(text);
    if (text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }
    printf("Enter the numeric key (digits only): ");
    fgets(key, sizeof(key), stdin);

    // Remove newline character from key if present
    len = strlen(key);
    if (key[len - 1] == '\n') {
        key[len - 1] = '\0';
    }

    // Validate the key (digits only)
    for (int i = 0; i < strlen(key); i++) {
        if (!isdigit(key[i])) {
            printf("Invalid key. Only digits (0-9) are allowed.\n");
            return 1;
        }
    }

    // Generate the full key based on the text length and the numeric key
    generateNumericKey(text, key, fullKey);

    int resultIndex = 0;
    for (int i = 0; i < strlen(text); ++i) {
        char ch = text[i];

        if (isalpha(ch)) {
            int isLower = islower(ch);
            char base = isLower ? 'a' : 'A';

            int shift = fullKey[i] - '0'; 

            if (choice == 1) {  // Encryption
                ch = (ch - base + shift) % 26 + base;
            } else {  // Decryption
                ch = (ch - base - shift + 26) % 26 + base;
            }

            result[resultIndex++] = ch;
        } else {
            result[resultIndex++] = ch; 
        }
    }

    result[resultIndex] ='\0'; 

    if (choice == 1) {
        printf("Encrypted message: %s\n", result);
    } else {
        printf("Decrypted message: %s\n", result);
    }

    return 0;
}
