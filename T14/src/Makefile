CC       := gcc
CFLAGS   := -std=c11 -Wall -Wextra -Werror

SRC_DIR  := .
BUILD    := ../build

STAGE_SORT    := state_sort
STAGE_SEARCH  := state_search

BIN1     := $(BUILD)/Quest_1
BIN2     := $(BUILD)/Quest_2

SRC1     := $(SRC_DIR)/state_sort.c
SRC2     := $(SRC_DIR)/state_search.c

.PHONY: all $(STAGE_SORT) $(STAGE_SEARCH) clean

all: $(STAGE_SORT) $(STAGE_SEARCH)

$(STAGE_SORT): $(BIN1)
$(STAGE_SEARCH): $(BIN2)

$(BIN1): $(SRC1)
	$(CC) $(CFLAGS) $< -o $@

$(BIN2): $(SRC2)
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(BUILD)/*
