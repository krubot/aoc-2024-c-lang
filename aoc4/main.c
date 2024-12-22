#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 141
#define MAX_HEIGHT 141

int main(void) {
	FILE *file = fopen("input.txt", "r");

	if (file == NULL) {
		perror("error");
		return EXIT_FAILURE;
	}

	char buffer[MAX_HEIGHT][MAX_LENGTH];
	int row = 0, col = 0;

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            row++;
            col = 0;
        } else {
            if (row < MAX_HEIGHT && col < MAX_LENGTH) {
                buffer[row][col++] = ch;
            }
        }
    }

	fclose(file);

	int count = 0;

	for (int i = 0; i < MAX_LENGTH; i++) {
		for (int j = 0; j < MAX_HEIGHT; j++) {
			if (buffer[i][j] == 'X' && buffer[i+1][j] == 'M' && buffer[i+2][j] == 'A' && buffer[i+3][j] == 'S') {
				count = count + 1;	
			}
			if (buffer[i][j] == 'S' && buffer[i+1][j] == 'A' && buffer[i+2][j] == 'M' && buffer[i+3][j] == 'X') {
				count = count + 1;
			}
		}
	}

	for (int i = 0; i < MAX_LENGTH; i++) {
		for (int j = 0; j < MAX_HEIGHT; j++) {
			if (buffer[i][j] == 'X' && buffer[i][j+1] == 'M' && buffer[i][j+2] == 'A' && buffer[i][j+3] == 'S') {
				count = count + 1;
			}
			if (buffer[i][j] == 'S' && buffer[i][j+1] == 'A' && buffer[i][j+2] == 'M' && buffer[i][j+3] == 'X') {
				count = count + 1;
			}
		}
	}

	for (int i = 0; i < MAX_LENGTH; i++) {
		for (int j = 0; j < MAX_HEIGHT; j++) {
			if (buffer[i][j] == 'X' && buffer[i+1][j+1] == 'M' && buffer[i+2][j+2] == 'A' && buffer[i+3][j+3] == 'S') {
				count = count + 1;
			}
			if (buffer[i][j] == 'S' && buffer[i+1][j+1] == 'A' && buffer[i+2][j+2] == 'M' && buffer[i+3][j+3] == 'X') {
				count = count + 1;
			}
		}
	}

	for (int i = 0; i < MAX_LENGTH; i++) {
		for (int j = 0; j < MAX_HEIGHT; j++) {
			if (buffer[i][j] == 'X' && buffer[i+1][j-1] == 'M' && buffer[i+2][j-2] == 'A' && buffer[i+3][j-3] == 'S') {
				count = count + 1;
			}
			if (buffer[i][j] == 'S' && buffer[i+1][j-1] == 'A' && buffer[i+2][j-2] == 'M' && buffer[i+3][j-3] == 'X') {
				count = count + 1;
			}
		}
	}
	
	printf("Answer1: %d\n", count);

	int count2 = 0;

	for (int i = 1; i < MAX_LENGTH - 1; i++) {
		for (int j = 1; j < MAX_HEIGHT - 1; j++) {
			if (buffer[i][j] == 'A') {
				if (buffer[i-1][j-1] == 'M' && buffer[i+1][j+1] == 'S' && buffer[i-1][j+1] == 'M' && buffer[i+1][j-1] == 'S') {
					count2 = count2 + 1;
				}
				if (buffer[i-1][j-1] == 'S' && buffer[i+1][j+1] == 'M' && buffer[i-1][j+1] == 'S' && buffer[i+1][j-1] == 'M') {
					count2 = count2 + 1;
				}
				if (buffer[i-1][j-1] == 'M' && buffer[i+1][j+1] == 'S' && buffer[i-1][j+1] == 'S' && buffer[i+1][j-1] == 'M') {
					count2 = count2 + 1;
				}
				if (buffer[i-1][j-1] == 'S' && buffer[i+1][j+1] == 'M' && buffer[i-1][j+1] == 'M' && buffer[i+1][j-1] == 'S') {
					count2 = count2 + 1;
				}
			}
		}
	}

	printf("Answer2: %d\n",count2);

	return 0;
}
