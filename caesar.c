#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], int shift) {
    int i;
    char ch;
    for(i = 0; text[i] != '\0'; i++) {
        ch = text[i];
        if(isalpha(ch)) {
            if(islower(ch)) {
                ch = (ch - 'a' + shift) % 26 + 'a';
            }
            else {
                ch = (ch - 'A' + shift) % 26 + 'A';
            }
            text[i] = ch;
        }
    }
}

void decrypt(char text[], int shift) {
    encrypt(text, (26 - shift) % 26);
}

int main() {
    char text[100];
    int shift, choice;
    
    printf("Caesar Cipher Implementation\n");
    printf("----------------------------\n");
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    
    if(text[strlen(text) - 1] == '\n') {
        text[strlen(text) - 1] = '\0';
    }
    
    printf("Enter the shift value (1-25): ");
    scanf("%d", &shift);
    shift = shift % 26;
    printf("\nChoose operation:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);
    
    if(choice == 1) {
        encrypt(text, shift);
        printf("\nEncrypted text: %s\n", text);
    }
    else if(choice == 2) {
        decrypt(text, shift);
        printf("\nDecrypted text: %s\n", text);
    }
    else {
        printf("\nInvalid choice!\n");
    }
    return 0;
}