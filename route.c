#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

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

// Display the matrix
void displayMatrix(char matrix[][MAX_SIZE], int rows, int cols) {
    printf("\nMatrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to encrypt using route cipher with specified route
void encrypt(char *plaintext, int rows, int cols, int routeOption) {
    char matrix[MAX_SIZE][MAX_SIZE];
    char processed[MAX_SIZE];
    char ciphertext[MAX_SIZE];
    int k = 0, index = 0;
    
    // Process the plaintext
    processText(plaintext, processed);
    int len = strlen(processed);
    
    // Fill the matrix row by row
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (k < len) {
                matrix[i][j] = processed[k++];
            } else {
                // Pad with 'X' if plaintext is shorter
                matrix[i][j] = 'X';
            }
        }
    }
    
    // Display the matrix
    displayMatrix(matrix, rows, cols);
    
    // Read in specified route
    switch (routeOption) {
        case 1: // Horizontal Route from top-left
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    ciphertext[index++] = matrix[i][j];
                }
            }
            break;
            
        case 2: // Horizontal Lines from top-left (zigzag)
            for (int i = 0; i < rows; i++) {
                if (i % 2 == 0) {
                    for (int j = 0; j < cols; j++) {
                        ciphertext[index++] = matrix[i][j];
                    }
                } else {
                    for (int j = cols - 1; j >= 0; j--) {
                        ciphertext[index++] = matrix[i][j];
                    }
                }
            }
            break;
            
        case 3: // Vertical Route from top-left
            for (int j = 0; j < cols; j++) {
                for (int i = 0; i < rows; i++) {
                    ciphertext[index++] = matrix[i][j];
                }
            }
            break;
            
        case 4: // Vertical Lines from top-left (zigzag)
            for (int j = 0; j < cols; j++) {
                if (j % 2 == 0) {
                    for (int i = 0; i < rows; i++) {
                        ciphertext[index++] = matrix[i][j];
                    }
                } else {
                    for (int i = rows - 1; i >= 0; i--) {
                        ciphertext[index++] = matrix[i][j];
                    }
                }
            }
            break;
            
        case 5: // Horizontal Route from top-right
            for (int i = 0; i < rows; i++) {
                for (int j = cols - 1; j >= 0; j--) {
                    ciphertext[index++] = matrix[i][j];
                }
            }
            break;
            
        case 6: // Horizontal Lines from top-right (zigzag)
            for (int i = 0; i < rows; i++) {
                if (i % 2 == 0) {
                    for (int j = cols - 1; j >= 0; j--) {
                        ciphertext[index++] = matrix[i][j];
                    }
                } else {
                    for (int j = 0; j < cols; j++) {
                        ciphertext[index++] = matrix[i][j];
                    }
                }
            }
            break;
            
        case 7: // Vertical Route from top-right
            for (int j = cols - 1; j >= 0; j--) {
                for (int i = 0; i < rows; i++) {
                    ciphertext[index++] = matrix[i][j];
                }
            }
            break;
            
        case 8: // Vertical Lines from top-right (zigzag)
            for (int j = cols - 1; j >= 0; j--) {
                if (j % 2 == 0) {
                    for (int i = 0; i < rows; i++) {
                        ciphertext[index++] = matrix[i][j];
                    }
                } else {
                    for (int i = rows - 1; i >= 0; i--) {
                        ciphertext[index++] = matrix[i][j];
                    }
                }
            }
            break;
            
        case 9: // Horizontal Route from bottom-right
            for (int i = rows - 1; i >= 0; i--) {
                for (int j = cols - 1; j >= 0; j--) {
                    ciphertext[index++] = matrix[i][j];
                }
            }
            break;
            
        case 10: // Horizontal Lines from bottom-right (zigzag)
            for (int i = rows - 1; i >= 0; i--) {
                if ((rows - 1 - i) % 2 == 0) {
                    for (int j = cols - 1; j >= 0; j--) {
                        ciphertext[index++] = matrix[i][j];
                    }
                } else {
                    for (int j = 0; j < cols; j++) {
                        ciphertext[index++] = matrix[i][j];
                    }
                }
            }
            break;
            
        case 11: // Vertical Route from bottom-right
            for (int j = cols - 1; j >= 0; j--) {
                for (int i = rows - 1; i >= 0; i--) {
                    ciphertext[index++] = matrix[i][j];
                }
            }
            break;
            
        case 12: // Vertical Lines from bottom-right (zigzag)
            for (int j = cols - 1; j >= 0; j--) {
                if ((cols - 1 - j) % 2 == 0) {
                    for (int i = rows - 1; i >= 0; i--) {
                        ciphertext[index++] = matrix[i][j];
                    }
                } else {
                    for (int i = 0; i < rows; i++) {
                        ciphertext[index++] = matrix[i][j];
                    }
                }
            }
            break;
            
        case 13: // Horizontal Route from bottom-left
            for (int i = rows - 1; i >= 0; i--) {
                for (int j = 0; j < cols; j++) {
                    ciphertext[index++] = matrix[i][j];
                }
            }
            break;
            
        case 14: // Horizontal Lines from bottom-left (zigzag)
            for (int i = rows - 1; i >= 0; i--) {
                if ((rows - 1 - i) % 2 == 0) {
                    for (int j = 0; j < cols; j++) {
                        ciphertext[index++] = matrix[i][j];
                    }
                } else {
                    for (int j = cols - 1; j >= 0; j--) {
                        ciphertext[index++] = matrix[i][j];
                    }
                }
            }
            break;
            
        case 15: // Vertical Route from bottom-left
            for (int j = 0; j < cols; j++) {
                for (int i = rows - 1; i >= 0; i--) {
                    ciphertext[index++] = matrix[i][j];
                }
            }
            break;
            
        case 16: // Vertical Lines from bottom-left (zigzag)
            for (int j = 0; j < cols; j++) {
                if (j % 2 == 0) {
                    for (int i = rows - 1; i >= 0; i--) {
                        ciphertext[index++] = matrix[i][j];
                    }
                } else {
                    for (int i = 0; i < rows; i++) {
                        ciphertext[index++] = matrix[i][j];
                    }
                }
            }
            break;
            
        default:
            printf("Invalid route option!\n");
            return;
    }
    
    ciphertext[index] = '\0';
    printf("\nEncrypted text: %s\n", ciphertext);
}

// Function to decrypt using route cipher with specified route
void decrypt(char *ciphertext, int rows, int cols, int routeOption) {
    char matrix[MAX_SIZE][MAX_SIZE];
    int len = strlen(ciphertext);
    int index = 0;
    char plaintext[MAX_SIZE];
    
    // Initialize matrix with placeholder
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = '.';
        }
    }
    
    // Fill matrix in specified route
    switch (routeOption) {
        case 1: // Horizontal Route from top-left
            for (int i = 0; i < rows && index < len; i++) {
                for (int j = 0; j < cols && index < len; j++) {
                    matrix[i][j] = ciphertext[index++];
                }
            }
            break;
            
        case 2: // Horizontal Lines from top-left (zigzag)
            for (int i = 0; i < rows && index < len; i++) {
                if (i % 2 == 0) {
                    for (int j = 0; j < cols && index < len; j++) {
                        matrix[i][j] = ciphertext[index++];
                    }
                } else {
                    for (int j = cols - 1; j >= 0 && index < len; j--) {
                        matrix[i][j] = ciphertext[index++];
                    }
                }
            }
            break;
            
        case 3: // Vertical Route from top-left
            for (int j = 0; j < cols && index < len; j++) {
                for (int i = 0; i < rows && index < len; i++) {
                    matrix[i][j] = ciphertext[index++];
                }
            }
            break;
            
        case 4: // Vertical Lines from top-left (zigzag)
            for (int j = 0; j < cols && index < len; j++) {
                if (j % 2 == 0) {
                    for (int i = 0; i < rows && index < len; i++) {
                        matrix[i][j] = ciphertext[index++];
                    }
                } else {
                    for (int i = rows - 1; i >= 0 && index < len; i--) {
                        matrix[i][j] = ciphertext[index++];
                    }
                }
            }
            break;
            
        case 5: // Horizontal Route from top-right
            for (int i = 0; i < rows && index < len; i++) {
                for (int j = cols - 1; j >= 0 && index < len; j--) {
                    matrix[i][j] = ciphertext[index++];
                }
            }
            break;
            
        case 6: // Horizontal Lines from top-right (zigzag)
            for (int i = 0; i < rows && index < len; i++) {
                if (i % 2 == 0) {
                    for (int j = cols - 1; j >= 0 && index < len; j--) {
                        matrix[i][j] = ciphertext[index++];
                    }
                } else {
                    for (int j = 0; j < cols && index < len; j++) {
                        matrix[i][j] = ciphertext[index++];
                    }
                }
            }
            break;
            
        case 7: // Vertical Route from top-right
            for (int j = cols - 1; j >= 0 && index < len; j--) {
                for (int i = 0; i < rows && index < len; i++) {
                    matrix[i][j] = ciphertext[index++];
                }
            }
            break;
            
        case 8: // Vertical Lines from top-right (zigzag)
            for (int j = cols - 1; j >= 0 && index < len; j--) {
                if (j % 2 == 0) {
                    for (int i = 0; i < rows && index < len; i++) {
                        matrix[i][j] = ciphertext[index++];
                    }
                } else {
                    for (int i = rows - 1; i >= 0 && index < len; i--) {
                        matrix[i][j] = ciphertext[index++];
                    }
                }
            }
            break;
            
        case 9: // Horizontal Route from bottom-right
            for (int i = rows - 1; i >= 0 && index < len; i--) {
                for (int j = cols - 1; j >= 0 && index < len; j--) {
                    matrix[i][j] = ciphertext[index++];
                }
            }
            break;
            
        case 10: // Horizontal Lines from bottom-right (zigzag)
            for (int i = rows - 1; i >= 0 && index < len; i--) {
                if ((rows - 1 - i) % 2 == 0) {
                    for (int j = cols - 1; j >= 0 && index < len; j--) {
                        matrix[i][j] = ciphertext[index++];
                    }
                } else {
                    for (int j = 0; j < cols && index < len; j++) {
                        matrix[i][j] = ciphertext[index++];
                    }
                }
            }
            break;
            
        case 11: // Vertical Route from bottom-right
            for (int j = cols - 1; j >= 0 && index < len; j--) {
                for (int i = rows - 1; i >= 0 && index < len; i--) {
                    matrix[i][j] = ciphertext[index++];
                }
            }
            break;
            
        case 12: // Vertical Lines from bottom-right (zigzag)
            for (int j = cols - 1; j >= 0 && index < len; j--) {
                if ((cols - 1 - j) % 2 == 0) {
                    for (int i = rows - 1; i >= 0 && index < len; i--) {
                        matrix[i][j] = ciphertext[index++];
                    }
                } else {
                    for (int i = 0; i < rows && index < len; i++) {
                        matrix[i][j] = ciphertext[index++];
                    }
                }
            }
            break;
            
        case 13: // Horizontal Route from bottom-left
            for (int i = rows - 1; i >= 0 && index < len; i--) {
                for (int j = 0; j < cols && index < len; j++) {
                    matrix[i][j] = ciphertext[index++];
                }
            }
            break;
            
        case 14: // Horizontal Lines from bottom-left (zigzag)
            for (int i = rows - 1; i >= 0 && index < len; i--) {
                if ((rows - 1 - i) % 2 == 0) {
                    for (int j = 0; j < cols && index < len; j++) {
                        matrix[i][j] = ciphertext[index++];
                    }
                } else {
                    for (int j = cols - 1; j >= 0 && index < len; j--) {
                        matrix[i][j] = ciphertext[index++];
                    }
                }
            }
            break;
            
        case 15: // Vertical Route from bottom-left
            for (int j = 0; j < cols && index < len; j++) {
                for (int i = rows - 1; i >= 0 && index < len; i--) {
                    matrix[i][j] = ciphertext[index++];
                }
            }
            break;
            
        case 16: // Vertical Lines from bottom-left (zigzag)
            for (int j = 0; j < cols && index < len; j++) {
                if (j % 2 == 0) {
                    for (int i = rows - 1; i >= 0 && index < len; i--) {
                        matrix[i][j] = ciphertext[index++];
                    }
                } else {
                    for (int i = 0; i < rows && index < len; i++) {
                        matrix[i][j] = ciphertext[index++];
                    }
                }
            }
            break;
            
        default:
            printf("Invalid route option!\n");
            return;
    }
    
    // Display the matrix
    displayMatrix(matrix, rows, cols);
    
    // Read matrix row by row to get plaintext
    index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            plaintext[index++] = matrix[i][j];
        }
    }
    plaintext[index] = '\0';
    
    printf("\nDecrypted text: %s\n", plaintext);
}

// Display menu for route options
void displayRouteMenu() {
    printf("\nROUTE OPTIONS:\n");
    printf("1. Horizontal Route from top-left\n");
    printf("2. Horizontal Lines from top-left (zigzag)\n");
    printf("3. Vertical Route from top-left\n");
    printf("4. Vertical Lines from top-left (zigzag)\n");
    printf("5. Horizontal Route from top-right\n");
    printf("6. Horizontal Lines from top-right (zigzag)\n");
    printf("7. Vertical Route from top-right\n");
    printf("8. Vertical Lines from top-right (zigzag)\n");
    printf("9. Horizontal Route from bottom-right\n");
    printf("10. Horizontal Lines from bottom-right (zigzag)\n");
    printf("11. Vertical Route from bottom-right\n");
    printf("12. Vertical Lines from bottom-right (zigzag)\n");
    printf("13. Horizontal Route from bottom-left\n");
    printf("14. Horizontal Lines from bottom-left (zigzag)\n");
    printf("15. Vertical Route from bottom-left\n");
    printf("16. Vertical Lines from bottom-left (zigzag)\n");
}

int main() {
    char text[MAX_SIZE];
    int choice, rows, cols, routeOption;
    
    printf("=== ROUTE CIPHER PROGRAM ===\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    getchar(); // Clear input buffer
    
    if (choice == 1) {
        printf("\nEnter the plaintext to encrypt: ");
        fgets(text, MAX_SIZE, stdin);
        text[strcspn(text, "\n")] = '\0'; // Remove newline
        
        printf("Enter the number of rows for the matrix: ");
        scanf("%d", &rows);
        printf("Enter the number of columns for the matrix: ");
        scanf("%d", &cols);
        
        displayRouteMenu();
        printf("\nSelect a route option (1-16): ");
        scanf("%d", &routeOption);
        
        encrypt(text, rows, cols, routeOption);
    } 
    else if (choice == 2) {
        printf("\nEnter the ciphertext to decrypt: ");
        fgets(text, MAX_SIZE, stdin);
        text[strcspn(text, "\n")] = '\0'; // Remove newline
        
        printf("Enter the number of rows for the matrix: ");
        scanf("%d", &rows);
        printf("Enter the number of columns for the matrix: ");
        scanf("%d", &cols);
        
        displayRouteMenu();
        printf("\nSelect a route option (1-16): ");
        scanf("%d", &routeOption);
        
        decrypt(text, rows, cols, routeOption);
    } 
    else {
        printf("Invalid choice!\n");
    }
    
    return 0;
}