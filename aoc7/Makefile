# Variables
CC = clang
CFLAGS = -Wall -Wextra -std=c17 -O2 -lm
LDFLAGS =
TARGET = main
SRC = main.c

# Targets
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

fmt:
	clang-format -i $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean run
