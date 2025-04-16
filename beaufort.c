#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateKey(const char* text, const char* keyword, char* key) {
    int textLen = strlen(text);
    int keyLen = strlen(keyword);
    int j = 0;

    for (int i = 0; i < textLen; ++i) {
        if (isalpha(text[i])) {
            key[i] = keyword[j % keyLen];
            j++;
        } else {
            key[i] = text[i];
        }
    }
    key[textLen] = '\0';
}

int main() {
    char text[1000], keyword[100], result[1000], key[1000];
    int choice;
    printf("Choose an option:\n");
    printf("1. Encrypt using Beaufort Cipher\n");
    printf("2. Decrypt using Beaufort Cipher\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    // Validate input
    if (choice != 1 && choice != 2) {
        printf("Invalid choice. Please enter 1 for Encrypt or 2 for Decrypt.\n");
        return 1;
    }
    printf("Enter the message: ");
    getchar(); // To consume the newline character left by scanf
    fgets(text, sizeof(text), stdin);

    // Remove newline character at the end of the string if present
    size_t len = strlen(text);
    if (text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);

    // Remove newline character from keyword if present
    len = strlen(keyword);
    if (keyword[len - 1] == '\n') {
        keyword[len - 1] = '\0';
    }

    // Generate the full key based on the text length and the keyword
    generateKey(text, keyword, key);

    int resultIndex = 0;
    for (int i = 0; i < strlen(text); ++i) {
        char ch = text[i];

        if (isalpha(ch)) {
            int isLower = islower(ch);
            char base = isLower ? 'a' : 'A';

            int keyVal = tolower(key[i]) - 'a';
            int plainVal = tolower(ch) - 'a';
            int cipherVal = (keyVal - plainVal+26) % 26;
            char cipherChar = isLower ? ('a'+cipherVal) : ('A'+cipherVal);

            result[resultIndex++] = cipherChar;
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
