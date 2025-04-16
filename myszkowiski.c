#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000
#define MAX_KEY_SIZE 100

// Structure to store column indices with same key letter
typedef struct {
    int indices[MAX_KEY_SIZE];
    int count;
} ColumnGroup;

// Function to remove spaces and convert to uppercase
void processText(char *text, char *result) {
    int j = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            result[j++] = toupper(text[i]);
        }
    }
    result[j] = '\0';
}

// Function to find unique characters in key and their positions
void analyzeKey(char *key, int keyLen, ColumnGroup groups[]) {
    char uniqueChars[MAX_KEY_SIZE];
    int uniqueCount = 0;
    
    // Find unique characters in the key
    for (int i = 0; i < keyLen; i++) {
        int found = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (key[i] == uniqueChars[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            uniqueChars[uniqueCount++] = key[i];
        }
    }
    
    // Sort unique characters alphabetically
    for (int i = 0; i < uniqueCount - 1; i++) {
        for (int j = i + 1; j < uniqueCount; j++) {
            if (uniqueChars[i] > uniqueChars[j]) {
                char temp = uniqueChars[i];
                uniqueChars[i] = uniqueChars[j];
                uniqueChars[j] = temp;
            }
        }
    }
    
    // Initialize column groups
    for (int i = 0; i < uniqueCount; i++) {
        groups[i].count = 0;
    }
    
    // Group columns by character
    for (int i = 0; i < uniqueCount; i++) {
        for (int j = 0; j < keyLen; j++) {
            if (key[j] == uniqueChars[i]) {
                groups[i].indices[groups[i].count++] = j;
            }
        }
    }
    
    printf("\nKey analysis:\n");
    for (int i = 0; i < uniqueCount; i++) {
        printf("Character '%c' appears at positions: ", uniqueChars[i]);
        for (int j = 0; j < groups[i].count; j++) {
            printf("%d ", groups[i].indices[j]);
        }
        printf("\n");
    }
}

// Function to encrypt using Myszkowski cipher
void encrypt(char *plaintext, char *key) {
    char processed[MAX_SIZE];
    processText(plaintext, processed);
    
    int keyLen = strlen(key);
    char keyUpper[MAX_KEY_SIZE];
    processText(key, keyUpper);
    keyLen = strlen(keyUpper); 
    
    int ptLen = strlen(processed);
    int rows = (ptLen + keyLen - 1) / keyLen; 
    
    // Create the matrix
    char matrix[MAX_SIZE][MAX_KEY_SIZE];
    int k = 0;
    
    // Fill the matrix row by row
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < keyLen; j++) {
            if (k < ptLen) {
                matrix[i][j] = processed[k++];
            } else {
                matrix[i][j] = 'X'; // Padding
            }
        }
    }
    
    // Display the matrix
    printf("\nPlaintext Matrix:\n  ");
    for (int j = 0; j < keyLen; j++) {
        printf("%c ", keyUpper[j]);
    }
    printf("\n");
    
    for (int i = 0; i < rows; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < keyLen; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // Analyze the key to find groups of columns
    ColumnGroup groups[MAX_KEY_SIZE];
    analyzeKey(keyUpper, keyLen, groups);
    
    // Generate ciphertext by reading columns according to key order
    char ciphertext[MAX_SIZE];
    int ctIndex = 0;
    
    // Process each group
    for (int g = 0; groups[g].count > 0; g++) {
        // For columns in the same group, read row by row
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < groups[g].count; j++) {
                int col = groups[g].indices[j];
                if (i < rows && col < keyLen && !(i == rows - 1 && matrix[i][col] == 'X')) {
                    ciphertext[ctIndex++] = matrix[i][col];
                }
            }
        }
    }
    
    ciphertext[ctIndex] = '\0';
    printf("\nEncrypted text: %s\n", ciphertext);
}

// Function to decrypt using Myszkowski cipher
void decrypt(char *ciphertext, char *key) {
    char processed[MAX_SIZE];
    processText(ciphertext, processed);
    
    int keyLen = strlen(key);
    char keyUpper[MAX_KEY_SIZE];
    processText(key, keyUpper);
    keyLen = strlen(keyUpper);
    
    int ctLen = strlen(processed);
    int rows = (ctLen + keyLen - 1) / keyLen; 
    
    // Create the matrix (initialized with placeholders)
    char matrix[MAX_SIZE][MAX_KEY_SIZE];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < keyLen; j++) {
            matrix[i][j] = '.';
        }
    }
    
    // Analyze the key to find groups of columns
    ColumnGroup groups[MAX_KEY_SIZE];
    analyzeKey(keyUpper, keyLen, groups);
    
    // Fill the matrix according to Myszkowski pattern
    int ctIndex = 0;
    
    // Process each group
    for (int g = 0; groups[g].count > 0; g++) {
        // For columns in the same group, fill row by row
        for (int i = 0; i < rows && ctIndex < ctLen; i++) {
            for (int j = 0; j < groups[g].count && ctIndex < ctLen; j++) {
                int col = groups[g].indices[j];
                if (i < rows && col < keyLen) {
                    matrix[i][col] = processed[ctIndex++];
                }
            }
        }
    }
    
    // Display the filled matrix
    printf("\nDecryption Matrix:\n  ");
    for (int j = 0; j < keyLen; j++) {
        printf("%c ", keyUpper[j]);
    }
    printf("\n");
    
    for (int i = 0; i < rows; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < keyLen; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // Read the plaintext row by row
    char plaintext[MAX_SIZE];
    int ptIndex = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < keyLen; j++) {
            if (matrix[i][j] != '.') {
                plaintext[ptIndex++] = matrix[i][j];
            }
        }
    }
    
    plaintext[ptIndex] = '\0';
    printf("\nDecrypted text: %s\n", plaintext);
}

int main() {
    char text[MAX_SIZE], key[MAX_KEY_SIZE];
    int choice;
    
    printf("=== MYSZKOWSKI TRANSPOSITION CIPHER ===\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    getchar(); 

    printf("Enter the key: ");
    fgets(key, MAX_KEY_SIZE, stdin);
    key[strcspn(key, "\n")] = '\0'; 
    
    if (choice == 1) {
        printf("Enter the plaintext to encrypt: ");
        fgets(text, MAX_SIZE, stdin);
        text[strcspn(text, "\n")] = '\0'; 
        encrypt(text, key);
    } 
    else if (choice == 2) {
        printf("Enter the ciphertext to decrypt: ");
        fgets(text, MAX_SIZE, stdin);
        text[strcspn(text, "\n")] = '\0'; 
        
        decrypt(text, key);
    } 
    else {
        printf("Invalid choice!\n");
    }
    
    return 0;
}