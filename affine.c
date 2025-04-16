#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to compute modular inverse of a under modulo m using Extended Euclidean Algorithm
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;

    return x1;
}
//check if a and m are coprime
int isCoprime(int a, int m) {
    while (m != 0) {
        int temp = m;
        m = a % m;
        a = temp;
    }
    return a == 1;
}

int main() {
    char text[1000];
    char choice;
    int a, b;

    printf("Do you want to (E)ncrypt or (D)ecrypt using Affine Cipher? ");
    scanf(" %c", &choice);
    choice = toupper(choice);

    if (choice != 'E' && choice != 'D') {
        printf("Invalid choice. Please enter E for Encrypt or D for Decrypt.\n");
        return 1;
    }

    printf("Enter the message: ");
    scanf("%s",text);

    printf("Enter key 'a' (must be coprime with 26): ");
    scanf("%d",&a);
    printf("Enter key 'b': ");
    scanf("%d",&b);

    if (!isCoprime(a, 26)) {
        printf("Invalid key 'a'. It must be coprime with 26.\n");
        return 1;
    }

    int a_inv = modInverse(a, 26); 

    for (int i = 0; i < strlen(text); ++i) {
        char ch = text[i];

        if (isalpha(ch)) {
            int isLower = islower(ch);
            char base = isLower ? 'a' : 'A';
            int x = ch - base;

            if (choice == 'E') {
                // Encryption: E(x) = (a * x + b) mod 26
                x = (a * x + b) % 26;
            } else {
                // Decryption: D(x) = a_inv * (x - b) mod 26
                x = (a_inv * (x - b + 26)) % 26;
            }

            ch = base + x;
        } else {
            printf("Invalid character in message. Only letters are allowed.\n");
            return 1;
        }

        text[i] = ch;
    }

    if (choice == 'E')
        printf("Encrypted message: %s\n", text);
    else
        printf("Decrypted message: %s\n", text);

    return 0;
}
