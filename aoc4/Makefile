# Variables
CC = clang
CFLAGS = -Wall -Wextra -std=c17 -O2
LDFLAGS =
TARGET = main
SRC = main.c

# Targets
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean run
