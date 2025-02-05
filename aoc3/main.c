#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 4096

int main(void) {
  FILE *file = fopen("input.txt", "r");

  if (file == NULL) {
    perror("error");
    return EXIT_FAILURE;
  }

  char buffer1[MAX_LINE_LENGTH];

  int sum1 = 0;

  while (fgets(buffer1, sizeof(buffer1), file)) {
    for (int i = 0; buffer1[i] != '\0'; i++) {
      if (buffer1[i] == 'm' && buffer1[i + 1] == 'u' && buffer1[i + 2] == 'l' &&
          buffer1[i + 3] == '(') {
        int j = 0;
        bool isDigitsVal1 = true;

        while (buffer1[i + 4 + j] != ',') {
          if (!isdigit(buffer1[i + 4 + j])) {
            isDigitsVal1 = false;
            break;
          }
          j++;
        }

        if (isDigitsVal1 == false) {
          continue;
        }

        char temp1[j + 1];
        strncpy(temp1, buffer1 + i + 4, j);
        temp1[j] = '\0';
        int val1 = atoi(temp1);

        int k = 0;
        bool isDigitsVal2 = true;

        while (buffer1[i + 5 + j + k] != ')') {
          if (!isdigit(buffer1[i + 5 + j + k])) {
            isDigitsVal2 = false;
            break;
          }
          k++;
        }

        if (isDigitsVal2 == false) {
          continue;
        }

        char temp2[k + 1];
        strncpy(temp2, buffer1 + i + 5 + j, k);
        temp2[k] = '\0';
        int val2 = atoi(temp2);

        char temp3[7 + j + k];
        strncpy(temp3, buffer1 + i, 6 + j + k);
        temp3[6 + j + k] = '\0';

        sum1 = sum1 + val1 * val2;
      }
    }
  }

  printf("Answer1: %d\n", sum1);

  rewind(file);

  char buffer2[MAX_LINE_LENGTH];

  int sum2 = 0;
  bool enabled = true;

  while (fgets(buffer2, sizeof(buffer2), file)) {
    for (int i = 0; buffer2[i] != '\0'; i++) {
      if (buffer2[i] == 'm' && buffer2[i + 1] == 'u' && buffer2[i + 2] == 'l' &&
          buffer2[i + 3] == '(') {
        int j = 0;
        bool isDigitsVal1 = true;

        while (buffer2[i + 4 + j] != ',') {
          if (!isdigit(buffer2[i + 4 + j])) {
            isDigitsVal1 = false;
            break;
          }
          j++;
        }

        if (isDigitsVal1 == false) {
          continue;
        }

        char temp1[j + 1];
        strncpy(temp1, buffer2 + i + 4, j);
        temp1[j] = '\0';
        int val1 = atoi(temp1);

        int k = 0;
        bool isDigitsVal2 = true;

        while (buffer2[i + 5 + j + k] != ')') {
          if (!isdigit(buffer2[i + 5 + j + k])) {
            isDigitsVal2 = false;
            break;
          }
          k++;
        }

        if (isDigitsVal2 == false) {
          continue;
        }

        char temp2[k + 1];
        strncpy(temp2, buffer2 + i + 5 + j, k);
        temp2[k] = '\0';
        int val2 = atoi(temp2);

        char temp3[7 + j + k];
        strncpy(temp3, buffer2 + i, 6 + j + k);
        temp3[6 + j + k] = '\0';

        if (enabled) {
          sum2 = sum2 + val1 * val2;
        }
      }
      if (buffer2[i] == 'd' && buffer2[i + 1] == 'o' && buffer2[i + 2] == 'n' &&
          buffer2[i + 3] == '\'' && buffer2[i + 4] == 't' &&
          buffer2[i + 5] == '(' && buffer2[i + 6] == ')') {
        enabled = false;
      }
      if (buffer2[i] == 'd' && buffer2[i + 1] == 'o' && buffer2[i + 2] == '(' &&
          buffer2[i + 3] == ')') {
        enabled = true;
      }
    }
  }

  printf("Answer2: %d\n", sum2);

  return 0;
}
