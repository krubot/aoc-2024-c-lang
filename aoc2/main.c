#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_NUMBERS_PER_LINE 100

/*
int *removeElement(int *arr, int size, int index) {
  int *new_arr = (int *)malloc((size) * sizeof(int));

  for (int i = 0, j = 0; i <= size; i++) {
    if (i != index) {
      new_arr[j++] = arr[i];
    }
  }

  return new_arr;
}

int test(int arr[], int size, int th) {
  for (int i = 0; i <= size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  if (size == 0) {
    return th;
  }

  int t;

  for (int i = 0; i <= size; i++) {
    int *new_arr = removeElement(arr, size, i);
    t = test(new_arr, size - 1, th + 1);
    free(new_arr);
  }

  return t;
}

int lowest(int arr[], int size, int th) {
  int *new_arr = removeElement(arr, size, 0);

  if (th == 1) {
	printf("here\n");
    for (int i = 0; i < size - 1; i++) {
      printf("%d ", new_arr[i]);
    }
    printf("\n");
  }

  int lowest = arrCheck(new_arr, size - 1, th + 1);

  if (th == 1) {
    printf("%d\n", lowest);
  }

  free(new_arr);
  for (int j = 1; j <= size; j++) {
    int *new_arr = removeElement(arr, size, j);

    if (th == 1) {
      for (int i = 0; i < size - 1; i++) {
        printf("%d ", new_arr[i]);
      }
      printf("\n");
    }

    int val = arrCheck(new_arr, size - 1, th + 1);

    if (th == 1) {
      printf("%d\n", val);
    }

    free(new_arr);
    if (val < lowest) {
      lowest = val;
    }
  }
  if (th == 1) {
    printf("%d\n",lowest);
  }
  return lowest;
}

int arrCheck(int arr[], int size, int th) {
  for (int i = 0; i < size; i++) {
    if (arr[0] < arr[size]) {
      if (arr[i] > arr[i + 1]) {
        return lowest(arr, size, th);
      } else {
        if (arr[i + 1] - arr[i] > 3) {
          return lowest(arr, size, th);
        } else if (arr[i] == arr[i + 1]) {
          return lowest(arr, size, th);
        }
      }
    } else if (arr[0] > arr[size]) {
      if (arr[i] < arr[i + 1]) {
        return lowest(arr, size, th);
      } else {
        if (arr[i] - arr[i + 1] > 3) {
          return lowest(arr, size, th);
        } else if (arr[i] == arr[i + 1]) {
          return lowest(arr, size, th);
        }
      }
    } else {
      return lowest(arr, size, th);
    }
  }

  return th;
}
*/

int main(void) {
  FILE *file = fopen("input2.txt", "r");

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

  // TODO: get this working
  /*
  int safe = 0;

  while (fgets(buffer, sizeof(buffer), file)) {
    int arrSize = 0;

    char *token = strtok(buffer, " \t\n");

    while (token != NULL) {
      arr[arrSize] = atoi(token);
      arrSize = arrSize + 1;
      token = strtok(NULL, " \t\n");
    }

    int th = arrCheck(arr, arrSize - 1, 0);

    if (th <= 1) {
      safe = safe + 1;
    }
  }

  printf("answer2: %d\n", safe);
  */

  return 0;
}
