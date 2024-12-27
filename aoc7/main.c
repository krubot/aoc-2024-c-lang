#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_ANSWER_SIZE 1000
#define MAX_VALUE_SIZE 100

enum Ops { ADD, MULTIPLY };

// Function to evaluate an expression with the given operator array
long long evaluateExpression(long long *values, enum Ops *ops, int size) {
    long long result = values[0];

    for (int i = 0; i < size - 1; i++) {
        if (ops[i] == ADD) {
            result += values[i + 1];
        } else if (ops[i] == MULTIPLY) {
            result *= values[i + 1];
        }
    }

    return result;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char ch;
    long long num = 0;
    int answerIndex = 0, valueIndex = 0;

    long long answers[MAX_ANSWER_SIZE];
    long long values[MAX_ANSWER_SIZE][MAX_VALUE_SIZE];
    int valueSizes[MAX_ANSWER_SIZE];

    while ((ch = fgetc(file)) != EOF) {
        if (isdigit(ch)) {
            num = num * 10 + (ch - '0');
        } else if (ch == ':') {
            answers[answerIndex] = num;
            num = 0;
        } else if (ch == ' ' && num != 0) {
            values[answerIndex][valueIndex++] = num;
            num = 0;
        } else if (ch == '\n' || ch == EOF) {
            if (num != 0) {
                values[answerIndex][valueIndex++] = num;
                num = 0;
            }
            valueSizes[answerIndex] = valueIndex;
            answerIndex++;
            valueIndex = 0;
        }
    }

    fclose(file);

    long long total = 0;

    // Process each equation and try all operator combinations
    for (int i = 0; i < answerIndex; i++) {
        long long ans = answers[i];
        int numValues = valueSizes[i];
        long long *valArray = values[i];

        bool match = false;

        // We will generate combinations of ADD and MULTIPLY for numValues - 1 positions
        int numCombinations = 1 << (numValues - 1);  // 2^(numValues-1)

        for (int j = 0; j < numCombinations; j++) {
            enum Ops ops[numValues - 1];

            // Generate the current combination of ADD/MULTIPLY
            for (int k = 0; k < numValues - 1; k++) {
                ops[k] = (j >> k) & 1 ? MULTIPLY : ADD;
            }

            // Evaluate the expression for this combination of operators
            long long result = evaluateExpression(valArray, ops, numValues);

            if (result == ans) {
                match = true;
                break;
            }
        }

        if (match) {
            total += ans;
        }
    }

    printf("Answer1: %lld\n", total);

    return 0;
}

