#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_TEXT 1000
#define MAX_NGRAM 10

typedef struct {
    char ngram[MAX_NGRAM];
    int count;
} NgramCount;

void preprocessText(const char* input, char* cleaned) {
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (isalpha(input[i])) {
            cleaned[j++] = toupper(input[i]);
        }
    }
    cleaned[j] = '\0';
}

int findNgram(NgramCount* arr, int size, const char* ngram) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].ngram, ngram) == 0) {
            return i;
        }
    }
    return -1;
}

void countNgrams(const char* text, int n) {
    int len = strlen(text);
    if (len < n) {
        printf("Text is too short for %d-grams.\n", n);
        return;
    }

    NgramCount ngrams[MAX_TEXT] = {0};
    int ngramCount = 0;

    for (int i = 0; i <= len - n; i++) {
        char current[MAX_NGRAM];
        strncpy(current, &text[i], n);
        current[n] = '\0';

        int idx = findNgram(ngrams, ngramCount, current);
        if (idx != -1) {
            ngrams[idx].count++;
        } else {
            strcpy(ngrams[ngramCount].ngram, current);
            ngrams[ngramCount].count = 1;
            ngramCount++;
        }
    }

    printf("\n--- %d-gram Frequencies ---\n", n);
    for (int i = 0; i < ngramCount; i++) {
        printf("%s : %d\n", ngrams[i].ngram, ngrams[i].count);
    }
}

int main() {
    char input[MAX_TEXT], cleaned[MAX_TEXT];
    int choice;

    printf("Enter the text: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // remove newline

    preprocessText(input, cleaned);

    printf("\nChoose N-gram type:\n");
    printf("1. Unigram\n");
    printf("2. Bigram (Digram)\n");
    printf("3. Trigram\n");
    printf("4. Tetragram\n");
    printf("Enter choice (1-4): ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 4) {
        countNgrams(cleaned, choice);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
