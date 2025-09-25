CC       := gcc
CFLAGS   := -std=c11 -Wall -Wextra -Werror

SRC       = cipher.c
BUILD_DIR = ../build
TARGET    = $(BUILD_DIR)/cipher

.PHONY: all cipher clean run

all: cipher
cipher: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

run: cipher
	$(TARGET)

clean:
	rm -rf $(BUILD_DIR)/*
