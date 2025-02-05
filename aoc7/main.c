#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ANSWER_SIZE 1000
#define MAX_VALUE_SIZE 100
#define MAX_CONCAT_SIZE 100

enum Ops { ADD, MULTIPLY, CONCAT };

// Function to evaluate an expression with the given operator array
long long evaluateExpression(long long *values, enum Ops *ops, int size) {
  long long result = values[0];

  for (int i = 0; i < size - 1; i++) {
    if (ops[i] == ADD) {
      result += values[i + 1];
    } else if (ops[i] == MULTIPLY) {
      result *= values[i + 1];
    } else if (ops[i] == CONCAT) {
      char buffer[MAX_CONCAT_SIZE];

      snprintf(buffer, sizeof(buffer), "%lld%lld", result, values[i + 1]);

      result = atoll(buffer);
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

    int numCombinations = pow(2, numValues - 1);

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

  long long total2 = 0;

  // Process each equation and try all operator combinations
  for (int i = 0; i < answerIndex; i++) {
    long long ans = answers[i];
    int numValues = valueSizes[i];
    long long *valArray = values[i];

    bool match = false;

    int numCombinations = pow(3, numValues - 1);

    for (int j = 0; j < numCombinations; j++) {
      enum Ops ops[numValues - 1];

      // Generate the current combination of ADD/MULTIPLY/CONCAT
      for (int k = 0; k < numValues - 1; k++) {
        int opIndex = (j / (int)pow(3, k)) % 3;

        if (opIndex == 0) {
          ops[k] = ADD;
        } else if (opIndex == 1) {
          ops[k] = MULTIPLY;
        } else {
          ops[k] = CONCAT;
        }
      }

      // Evaluate the expression for this combination of operators
      long long result = evaluateExpression(valArray, ops, numValues);

      if (result == ans) {
        match = true;
        break;
      }
    }

    if (match) {
      total2 += ans;
    }
  }

  printf("Answer2: %lld\n", total2);

  return 0;
}
