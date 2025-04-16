#include <stdio.h>
#include <string.h>
#include <ctype.h>

void augustCipher(char* text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        if (isalpha(ch)) {
            if (islower(ch)) {
                text[i] = 'a' + (ch - 'a' + shift + 26) % 26;
            } else if (isupper(ch)) {
                text[i] = 'A' + (ch - 'A' + shift + 26) % 26;
            }
        }
    }
}

int main() {
    char text[1000];
    int choice;

    printf("Enter the text to be encrypted/decrypted: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline character if it's at the end of the input
    size_t len = strlen(text);
    if (text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    printf("\nChoose operation:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    // Perform the corresponding operation
    if (choice == 1) {
       
        augustCipher(text, 1);
        printf("\nEncrypted Text: %s\n", text);
    } else if (choice == 2) {
       
        augustCipher(text, -1);
        printf("\nDecrypted Text: %s\n", text);
    } else {
        printf("\nInvalid choice!\n");
    }

    return 0;
}
