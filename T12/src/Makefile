CC = gcc
CFLAGS = -I.
SRC_DIR = .
BUILD_DIR = ../build

TARGET1 = $(BUILD_DIR)/Quest1
TARGET2 = $(BUILD_DIR)/Quest2

SOURCES_PRINT = $(SRC_DIR)/print_module.c
SOURCES_DOC = $(SRC_DIR)/documentation_module.c
SOURCES_MAIN = $(SRC_DIR)/main_module_entry_point.c

.PHONY: all Quest1 Quest2 clean

all: Quest1 Quest2

Quest1: $(TARGET1)

Quest2: $(TARGET2)

$(TARGET1): $(SOURCES_PRINT) $(SOURCES_MAIN)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET2): $(SOURCES_PRINT) $(SOURCES_DOC) $(SOURCES_MAIN)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -DQUEST2 $^ -o $@

clean:
	rm -rf $(BUILD_DIR)