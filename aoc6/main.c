#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LENGTH 1000
#define MAX_HEIGHT 1000

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Map {
	char** field;
	int fieldLength;
	int fieldHeight;
	enum Direction direction;
  bool outOfBounds;	
};

struct Map next(struct Map map) {
	int x;
	int y;

	for (int i = 0; i < map.fieldHeight; i++) {
		for (int j = 0; j < map.fieldLength; j++) {
			if (map.field[i][j] == '^') {
				x = i;
				y = j;
			}
    }
  }

	if (map.direction == UP) {
		if (x <= 0) {
			map.outOfBounds = true;
			map.field[x][y] = 'X';
		} else {	
			if (map.field[x-1][y] == '#') {
				map.direction = RIGHT;
			} else {
				map.field[x-1][y] = '^';
				map.field[x][y] = 'X';
			}
		}
	} else if (map.direction == RIGHT) {
		if (y + 1 >= map.fieldLength) {
			map.outOfBounds = true;
			map.field[x][y] = 'X';
		} else {
			if (map.field[x][y+1] == '#') {
				map.direction = DOWN;
			} else {
				map.field[x][y+1] = '^';
				map.field[x][y] = 'X';
			}
		}
	} else if (map.direction == DOWN) {
		if (x + 1 >= map.fieldHeight) {
			map.outOfBounds = true;
			map.field[x][y] = 'X';
		} else {
			if (map.field[x+1][y] == '#') {
				map.direction = LEFT;
			} else {
				map.field[x+1][y] = '^';
				map.field[x][y] = 'X';
			}
		}
	} else {
		if (y <= 0) {
			map.outOfBounds = true;
			map.field[x][y] = 'X';
		} else {
			if (map.field[x][y-1] == '#') {
				map.direction = UP;
			} else {
				map.field[x][y-1] = '^';
				map.field[x][y] = 'X';
			}
		}
	}

	return map;
}

int main(void) {
	FILE *file = fopen("input.txt","r");

	if (file == NULL) {
		perror("File open failed");
		return EXIT_FAILURE;	
	}

	char ch;
	int i = 0;
	int j = 0;
	int arrLength = 0;
	int arrHeight = 0;

	char** arr = (char**)malloc(MAX_LENGTH * sizeof(char*));

  for (int i = 0; i < MAX_LENGTH; i++) {
		arr[i] = (char*)malloc(MAX_HEIGHT * sizeof(char));
	}

	while((ch = fgetc(file)) != EOF) {
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

	struct Map map = {
		.field = arr,
		.fieldLength = arrLength,
		.fieldHeight = arrHeight,
		.direction = UP,
		.outOfBounds = false,
	};

	while (!map.outOfBounds) {
		map = next(map);
	}

	int count = 0;

	for (int i = 0; i < arrLength; i++) {
		for (int j = 0; j < arrHeight; j++) {
			if (map.field[i][j] == 'X') {
				count++;
			}
		}
	}

	printf("answer1: %d\n",count);

	for (int k = 0; k < MAX_HEIGHT; k++) {
		free(arr[k]);
  }
  free(arr);

	return 0;
}
