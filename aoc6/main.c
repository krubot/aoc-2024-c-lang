#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1000
#define MAX_HEIGHT 1000
#define FILE_NAME "input.txt"

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Field {
  char **field;
  int fieldLength;
  int fieldHeight;
};

struct Map {
  char **field;
  int fieldLength;
  int fieldHeight;
  enum Direction direction;
  bool outOfBounds;
};

struct Field fieldInit(void);
void freeField(char **field, int height);
struct Map next(struct Map map);

struct Map next(struct Map map) {
  int x = -1, y = -1;

  for (int i = 0; i < map.fieldHeight; i++) {
    for (int j = 0; j < map.fieldLength; j++) {
      if (map.field[i][j] == '^') {
        x = i;
        y = j;
        break;
      }
    }
    if (x != -1)
      break;
  }

  if (x == -1 || y == -1) {
    map.outOfBounds = true;
    return map;
  }

  if (map.direction == UP) {
    if (x <= 0) {
      map.outOfBounds = true;
      map.field[x][y] = 'X';
    } else if (map.field[x - 1][y] == '#') {
      map.direction = RIGHT;
    } else {
      map.field[x - 1][y] = '^';
      map.field[x][y] = 'X';
    }
  } else if (map.direction == RIGHT) {
    if (y + 1 >= map.fieldLength) {
      map.outOfBounds = true;
      map.field[x][y] = 'X';
    } else if (map.field[x][y + 1] == '#') {
      map.direction = DOWN;
    } else {
      map.field[x][y + 1] = '^';
      map.field[x][y] = 'X';
    }
  } else if (map.direction == DOWN) {
    if (x + 1 >= map.fieldHeight) {
      map.outOfBounds = true;
      map.field[x][y] = 'X';
    } else if (map.field[x + 1][y] == '#') {
      map.direction = LEFT;
    } else {
      map.field[x + 1][y] = '^';
      map.field[x][y] = 'X';
    }
  } else {
    if (y <= 0) {
      map.outOfBounds = true;
      map.field[x][y] = 'X';
    } else if (map.field[x][y - 1] == '#') {
      map.direction = UP;
    } else {
      map.field[x][y - 1] = '^';
      map.field[x][y] = 'X';
    }
  }

  return map;
}

struct Field fieldInit(void) {
  FILE *file = fopen(FILE_NAME, "r");
  if (!file) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  char ch;
  int i = 0, j = 0, arrLength = 0, arrHeight = 0;

  char **arr = (char **)malloc(MAX_LENGTH * sizeof(char *));
  for (int k = 0; k < MAX_LENGTH; k++) {
    arr[k] = (char *)malloc(MAX_HEIGHT * sizeof(char));
  }

  while ((ch = fgetc(file)) != EOF) {
    if (ch != '\n') {
      arr[i][j] = ch;
      j++;
      if (j > arrLength) {
        arrLength = j;
      }
    } else {
      i++;
      j = 0;
      if (i > arrHeight) {
        arrHeight = i;
      }
    }
  }

  fclose(file);

  struct Field field = {
      .field = arr,
      .fieldHeight = arrHeight + 1,
      .fieldLength = arrLength,
  };

  return field;
}

void freeField(char **field, int height) {
  for (int i = 0; i < height; i++) {
    free(field[i]);
  }
  free(field);
}

int main(void) {
  struct Field field = fieldInit();

  struct Map map = {
      .field = field.field,
      .fieldLength = field.fieldLength,
      .fieldHeight = field.fieldHeight,
      .direction = UP,
      .outOfBounds = false,
  };

  while (!map.outOfBounds) {
    map = next(map);
  }

  int count = 0;
  for (int i = 0; i < field.fieldHeight; i++) {
    for (int j = 0; j < field.fieldLength; j++) {
      if (map.field[i][j] == 'X') {
        count++;
      }
    }
  }
  printf("answer1: %d\n", count);

  // TODO: improve speed and memory profile
  int count2 = 0;

  for (int i = 0; i < field.fieldHeight; i++) {
    for (int j = 0; j < field.fieldLength; j++) {
      if (field.field[i][j] != '^') {
        struct Field tempField = fieldInit();
        tempField.field[i][j] = '#';

        struct Map tempMap = {
            .field = tempField.field,
            .fieldLength = tempField.fieldLength,
            .fieldHeight = tempField.fieldHeight,
            .direction = UP,
            .outOfBounds = false,
        };

        for (int k = 0; k < 10000; k++) {
          tempMap = next(tempMap);
          if (tempMap.outOfBounds) {
            break;
          }
        }

        if (!tempMap.outOfBounds) {
          count2++;
        }

        freeField(tempField.field, tempField.fieldHeight);
      }
    }
  }

  printf("answer2: %d\n", count2);

  freeField(field.field, field.fieldHeight);
  return 0;
}
