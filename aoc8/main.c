#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100
#define MAX_HEIGHT 100

struct Point {
  int x;
  int y;
};

struct PointsList {
  struct Point *points;
  int points_length;
};

struct PointsList locate_points(char field[MAX_LENGTH][MAX_HEIGHT],
                                int field_max_length, int field_max_height,
                                char c) {
  int point_index = 0;
  struct Point *arr =
      (struct Point *)malloc(MAX_LENGTH * MAX_HEIGHT * sizeof(struct Point));

  for (int j = 0; j < field_max_height; j++) {
    for (int i = 0; i < field_max_length; i++) {
      if (field[j][i] == c) {
        arr[point_index].x = i;
        arr[point_index].y = j;
        point_index++;
      }
    }
  }

  struct PointsList points_list = {
      .points = arr,
      .points_length = point_index,
  };

  return points_list;
}

int main() {
  FILE *file = fopen("input.txt", "r");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  char ch;
  int i = 0, j = 0;
  int field_max_length = 0, field_max_height = 0;
  char field[MAX_LENGTH][MAX_HEIGHT] = {0};

  while ((ch = fgetc(file)) != EOF) {
    if (isalnum(ch) || ch == '.') {
      field[j][i] = ch;
      i++;
    } else if (ch == '\n') {
      if (i > field_max_length)
        field_max_length = i;
      i = 0;
      j++;
    }
  }
  field_max_height = j;

  fclose(file);

	char anti_field[MAX_LENGTH][MAX_HEIGHT] = {0};

  for (int ch = 0; ch <= 127; ch++) {
    if (isalnum(ch)) {
      struct PointsList pl =
          locate_points(field, field_max_length, field_max_height, ch);

      for (int i = 0; i < pl.points_length; i++) {
        for (int j = i + 1; j < pl.points_length; j++) {
          int i1 = 2 * pl.points[i].x - pl.points[j].x;
          int j1 = 2 * pl.points[i].y - pl.points[j].y;

          int i2 = 2 * pl.points[j].x - pl.points[i].x;
          int j2 = 2 * pl.points[j].y - pl.points[i].y;

          if (0 <= i1 && i1 < field_max_length && 0 <= j1 &&
              j1 < field_max_height) {
						anti_field[j1][i1] = '#';
          }

          if (0 <= i2 && i2 < field_max_length && 0 <= j2 &&
              j2 < field_max_height) {
            anti_field[j2][i2] = '#';
          }
        }
      }
    }
  }

	int count = 0;

  for (int y = 0; y < field_max_height; y++) {
    for (int x = 0; x < field_max_length; x++) {
			if (anti_field[y][x] == '#') {
				count++;
			}
    }
  }

  printf("Answer1: %d\n", count);

  return 0;
}
