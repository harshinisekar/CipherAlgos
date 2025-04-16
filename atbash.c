#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to apply the Atbash transformation
void applyAtbash(char message[]) {
    for (int j = 0;message[j] !='\0';j++) {
        char current = message[j];
        
        if (isalpha(current)) {
            if (islower(current)) {
                message[j] = 'z'-(current -'a');
            } else {
                message[j] = 'Z'-(current -'A');
            }
        }
    }
}

int main() {
    char input[100];
    int option;

    printf(" Atbash Cipher Tool !!!\n");
    printf("Input your message: ");
    fgets(input, sizeof(input), stdin);
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    printf("\nSelect mode:\n");
    printf("1 -> Encrypt\n");
    printf("2 -> Decrypt\n");
    printf("Your choice: ");
    scanf("%d", &option);

    if (option == 1 || option == 2) {
        applyAtbash(input);
        printf("\nResult: %s\n", input);
    } else {
        printf("\nInvalid choice! Please enter 1 or 2.\n");
    }

    return 0;
}
