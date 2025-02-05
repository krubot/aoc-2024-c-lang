#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main(void) {
  int num1, num2;
  char line[256];

  FILE *file = fopen("input.txt", "r");

  if (file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  size_t lineCount = 0;
  char ch;

  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      lineCount++;
    }
  }

  rewind(file);

  int arr1[lineCount], arr2[lineCount];

  for (size_t i = 0; i < lineCount; i++) {
    if (fgets(line, sizeof(line), file)) {
      if (sscanf(line, "%d %d", &num1, &num2) == 2) {
        arr1[i] = num1;
        arr2[i] = num2;
      } else {
        perror("Error line isn't formated correctly");
      }
    } else {
      perror("Error return from fgets");
    }
  }

  qsort(arr1, lineCount, sizeof(int), compare);
  qsort(arr2, lineCount, sizeof(int), compare);

  int sum1 = 0;

  for (size_t i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++) {
    if (arr1[i] <= arr2[i]) {
      int diff = arr2[i] - arr1[i];
      sum1 = sum1 + diff;
    } else {
      int diff = arr1[i] - arr2[i];
      sum1 = sum1 + diff;
    }
  }

  printf("answer1: %d\n", sum1);

  int sum2 = 0;

  for (size_t i = 0; i < lineCount; i++) {
    int repeat = 0;
    for (size_t j = 0; j < lineCount; j++) {
      if (arr1[i] == arr2[j]) {
        repeat = repeat + 1;
      }
    }
    sum2 = sum2 + arr1[i] * repeat;
  }

  printf("answer2: %d\n", sum2);

  fclose(file);

  return 0;
}
