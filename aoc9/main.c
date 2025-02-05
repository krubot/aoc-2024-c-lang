#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000000

struct DM {
  int data[MAX_LENGTH];
  int data_length;
};

struct DMD {
  int data[MAX_LENGTH];
  int data_length;
};

int main() {
  FILE *file = fopen("input.txt", "r");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  char ch;

  struct DM dm = {.data = {}, .data_length = 0};

  struct DMD decode = {.data = {}, .data_length = 0};

  while ((ch = fgetc(file)) != EOF) {
    if (ch != '\n') {
      dm.data[dm.data_length] = ch - '0';
      dm.data_length++;
    }
  }

  int i = 0;
  int id = 0;
  bool block = true;
  int dots_num = 0;

  for (int j = 0; j < dm.data_length; j++) {
    if (block) {
      for (int k = 0; k < dm.data[j]; k++) {
        decode.data[i] = id;
        i++;
      }
      id++;
      block = false;
    } else {
      for (int k = 0; k < dm.data[j]; k++) {
        decode.data[i] = -1;
        dots_num++;
        i++;
      }
      block = true;
    }
  }

  decode.data_length = i;

  for (int i = 1; i <= dots_num; i++) {
    if (decode.data[decode.data_length - i] != -1) {
      int t = decode.data[decode.data_length - i];
      decode.data[decode.data_length - i] = -1;
      for (int j = 0; j < decode.data_length; j++) {
        if (decode.data[j] == -1) {
          decode.data[j] = t;
          break;
        }
      }
    }
  }

  int j = 0;
  long long int sum = 0;

  while (decode.data[j] != -1) {
    sum = sum + j * decode.data[j];
    j++;
  }

  printf("Answer1: %lld\n", sum);

  return 0;
}
