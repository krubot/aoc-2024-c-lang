#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_NUMBERS_PER_LINE 100

// Removing array value at index
int *removeElement(int *arr, int size, int index) {
  int *new_arr = (int *)malloc((size) * sizeof(int));

  for (int i = 0, j = 0; i <= size; i++) {
    if (i != index) {
      new_arr[j++] = arr[i];
    }
  }

  return new_arr;
}

// Checks array and returns the minimum elements to be removed to make it safe
int arrCheck(int arr[], int size, int th) {
  if (size == 1) {
    return th;
  }

  bool unsafe = false;

  for (int i = 0; i < size - 1; i++) {
    if (arr[0] < arr[size - 1]) {
      if (arr[i] > arr[i + 1]) {
        unsafe = true;
        break;
      } else {
        if (arr[i + 1] - arr[i] > 3) {
          unsafe = true;
          break;
        } else if (arr[i] == arr[i + 1]) {
          unsafe = true;
          break;
        }
      }
    } else if (arr[0] > arr[size - 1]) {
      if (arr[i] < arr[i + 1]) {
        unsafe = true;
        break;
      } else {
        if (arr[i] - arr[i + 1] > 3) {
          unsafe = true;
          break;
        } else if (arr[i] == arr[i + 1]) {
          unsafe = true;
          break;
        }
      }
    } else {
      unsafe = true;
      break;
    }
  }

  if (unsafe) {
    int t;

    int *new_arr = removeElement(arr, size, 0);
    t = arrCheck(new_arr, size - 1, th + 1);
    free(new_arr);

    for (int i = 1; i < size; i++) {
      int *new_arr = removeElement(arr, size, i);
      int val = arrCheck(new_arr, size - 1, th + 1);
      free(new_arr);

      if (val < t) {
        t = val;
      }
    }

    return t;
  } else {
    return th;
  }
}

int main(void) {
  FILE *file = fopen("input.txt", "r");

  if (file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  char buffer[MAX_LINE_LENGTH];
  int arr[MAX_NUMBERS_PER_LINE];
  int numberSafeReports = 0;

  while (fgets(buffer, sizeof(buffer), file)) {
    int numberCount = 0;

    char *token = strtok(buffer, " \t\n");

    while (token != NULL) {
      arr[numberCount] = atoi(token);
      numberCount = numberCount + 1;
      token = strtok(NULL, " \t\n");
    }

    bool unsafe = false;

    for (int i = 0; i + 1 < numberCount; i++) {
      if (arr[0] < arr[numberCount - 1]) {
        if (arr[i] > arr[i + 1]) {
          unsafe = true;
          break;
        } else {
          if (arr[i + 1] - arr[i] > 3) {
            unsafe = true;
            break;
          } else if (arr[i] == arr[i + 1]) {
            unsafe = true;
            break;
          }
        }
      } else if (arr[0] > arr[numberCount - 1]) {
        if (arr[i] < arr[i + 1]) {
          unsafe = true;
          break;
        } else {
          if (arr[i] - arr[i + 1] > 3) {
            unsafe = true;
            break;
          } else if (arr[i] == arr[i + 1]) {
            unsafe = true;
            break;
          }
        }
      } else {
        unsafe = true;
        break;
      }
    }

    if (!unsafe) {
      numberSafeReports = numberSafeReports + 1;
    }
  }

  printf("answer1: %d\n", numberSafeReports);

  rewind(file);

  int safe = 0;

  while (fgets(buffer, sizeof(buffer), file)) {
    int arrSize = 0;

    char *token = strtok(buffer, " \t\n");

    while (token != NULL) {
      arr[arrSize] = atoi(token);
      arrSize = arrSize + 1;
      token = strtok(NULL, " \t\n");
    }

    int th = arrCheck(arr, arrSize, 0);

    if (th <= 1) {
      safe = safe + 1;
    }
  }

  printf("answer2: %d\n", safe);

  return 0;
}
