CC ?= gcc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra

TARGET := task_allocator
SOURCE := src/task_allocator.c
EXAMPLE := examples/task_set.txt

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET) $(EXAMPLE)

clean:
	$(RM) $(TARGET)
