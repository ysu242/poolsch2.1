CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = modules_db
SOURCES = modules_db.c modules.c levels.c status_events.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

build_db: $(TARGET)

run: $(TARGET)
	./$(TARGET)