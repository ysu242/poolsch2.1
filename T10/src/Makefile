CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Isrc

SRC_FILES = src/s21_string.c src/s21_string_test.c
TARGET = build/Quest\ 1

strlen_tests: $(SRC_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_FILES)

clean:
	rm -f $(TARGET)

.PHONY: strlen_tests clean