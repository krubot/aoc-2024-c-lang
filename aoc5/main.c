#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 1000

bool check(int arr[], int arrSize, int a, int b) {
  int val1 = -1;
  int val2 = arrSize;

  for (int i = 0; i < arrSize; i++) {
    if (arr[i] == a) {
      val1 = i;
    }
    if (arr[i] == b) {
      val2 = i;
    }
    if (val1 != -1 && val2 != arrSize) {
      break;
    }
  }

  return val1 < val2;
}

int main() {
  FILE *file = fopen("input.txt", "r");
  if (file == NULL) {
    perror("File open failed");
    return EXIT_FAILURE;
  }

  // Dynamic memory allocation for conditionArr
  int **conditionArr = malloc(INITIAL_CAPACITY * sizeof(int *));
  if (!conditionArr) {
    perror("Memory allocation failed");
    return EXIT_FAILURE;
  }
  for (int i = 0; i < INITIAL_CAPACITY; i++) {
    conditionArr[i] = malloc(2 * sizeof(int));
    if (!conditionArr[i]) {
      perror("Memory allocation failed");
      return EXIT_FAILURE;
    }
  }

  int capacity = INITIAL_CAPACITY;
  int conditionArrSize = 0;
  char ch, prevChar = '\0';
  int num = 0;

  // Read conditions
  while ((ch = fgetc(file)) != EOF) {
    if (prevChar == '\n' && ch == '\n') {
      break;
    }
    if (isdigit(ch)) {
      num = num * 10 + (ch - '0');
    }
    if (ch == '|') {
      if (conditionArrSize >= capacity) {
        capacity *= 2;
        conditionArr = realloc(conditionArr, capacity * sizeof(int *));
        if (!conditionArr) {
          perror("Memory reallocation failed");
          return EXIT_FAILURE;
        }
        for (int i = conditionArrSize; i < capacity; i++) {
          conditionArr[i] = malloc(2 * sizeof(int));
          if (!conditionArr[i]) {
            perror("Memory allocation failed");
            return EXIT_FAILURE;
          }
        }
      }
      conditionArr[conditionArrSize][0] = num;
      num = 0;
    }
    if (ch == '\n') {
      conditionArr[conditionArrSize][1] = num;
      num = 0;
      conditionArrSize++;
    }
    prevChar = ch;
  }

  // Prepare for reading the lists
  int **list = malloc(INITIAL_CAPACITY * sizeof(int *));
  if (!list) {
    perror("Memory allocation failed");
    return EXIT_FAILURE;
  }
  for (int i = 0; i < INITIAL_CAPACITY; i++) {
    list[i] = malloc(INITIAL_CAPACITY * sizeof(int));
    if (!list[i]) {
      perror("Memory allocation failed");
      return EXIT_FAILURE;
    }
  }

  int *listArrSize = malloc(INITIAL_CAPACITY * sizeof(int));
  if (!listArrSize) {
    perror("Memory allocation failed");
    return EXIT_FAILURE;
  }

  int listCapacity = INITIAL_CAPACITY;
  int listIndex = 0, listArrIndex = 0;
  int num2 = 0;

  // Read lists
  while ((ch = fgetc(file)) != EOF) {
    if (isdigit(ch)) {
      num2 = num2 * 10 + (ch - '0');
    }
    if (ch == ',') {
      list[listIndex][listArrIndex++] = num2;
      num2 = 0;
    }
    if (ch == '\n') {
      list[listIndex][listArrIndex++] = num2;
      listArrSize[listIndex] = listArrIndex;
      listIndex++;
      listArrIndex = 0;
      num2 = 0;

      if (listIndex >= listCapacity) {
        listCapacity *= 2;
        list = realloc(list, listCapacity * sizeof(int *));
        if (!list) {
          perror("Memory reallocation failed");
          return EXIT_FAILURE;
        }
        for (int i = listIndex; i < listCapacity; i++) {
          list[i] = malloc(INITIAL_CAPACITY * sizeof(int));
          if (!list[i]) {
            perror("Memory allocation failed");
            return EXIT_FAILURE;
          }
        }
        listArrSize = realloc(listArrSize, listCapacity * sizeof(int));
        if (!listArrSize) {
          perror("Memory reallocation failed");
          return EXIT_FAILURE;
        }
      }
    }
  }

  // Compute the sum
  int sum = 0;
  for (int i = 0; i < listIndex; i++) {
    bool pass = true;
    for (int j = 0; j < conditionArrSize; j++) {
      if (!check(list[i], listArrSize[i], conditionArr[j][0],
                 conditionArr[j][1])) {
        pass = false;
        break;
      }
    }
    if (pass) {
      int middle = (listArrSize[i] - 1) / 2;
      sum += list[i][middle];
    }
  }

  printf("Answer1: %d\n", sum);

	/*
  // Compute the sum2
  int sum2 = 0;
  for (int i = 0; i < listIndex; i++) {
    bool pass = true;
    for (int j = 0; j < conditionArrSize; j++) {
      if (!check(list[i], listArrSize[i], conditionArr[j][0],
                 conditionArr[j][1])) {
        pass = false;
        break;
      }
    }
    if (!pass) {
      int middle = (listArrSize[i] - 1) / 2;
      sum2 += list[i][middle];
    }
  }

  printf("Answer2: %d\n", sum2);
	*/

  // Free memory
  for (int i = 0; i < capacity; i++) {
    free(conditionArr[i]);
  }
  free(conditionArr);

  for (int i = 0; i < listCapacity; i++) {
    free(list[i]);
  }
  free(list);
  free(listArrSize);

  fclose(file);
  return 0;
}
