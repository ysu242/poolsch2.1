CC       := gcc
CFLAGS   := -std=c11 -Wall -Wextra -Werror
SRC_DIR  := .
BUILD_DIR:= ../build
TARGET1  := Quest_1
TARGET2  := Quest_3
BIN1     := $(BUILD_DIR)/$(TARGET1)
BIN2     := $(BUILD_DIR)/$(TARGET2)

SRCS_DOOR := $(SRC_DIR)/dmanager_module.c
SRCS_STACK:= $(SRC_DIR)/stack_test.c $(SRC_DIR)/stack.c
OBJS_STACK:= $(SRCS_STACK:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

.PHONY: all door_struct stack_test run clean

all: door_struct stack_test

door_struct: $(BIN1)

$(BIN1): $(SRCS_DOOR) $(SRC_DIR)/door_struct.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

stack_test: $(BIN2)

$(BIN2): $(OBJS_STACK) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

run: door_struct
	$(BIN1)

clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN1) $(BIN2)
