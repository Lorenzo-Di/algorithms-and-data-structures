CC = gcc
INCLUDES = -Iinclude -Ilib/include
CFLAGS = -g $(INCLUDES) -Wall -Wextra -Wpedantic -Wconversion

LIB_SRC = $(wildcard lib/src/*.c)

SRC_DIR = $(filter-out src/main.c, $(wildcard src/*.c))

OBJ = $(patsubst %.c, build/%.o, $(LIB_SRC) $(SRC_DIR))

all: bin/main_ex4

bin/main_ex4: $(OBJ) build/src/main.o
	@mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/ bin/

rebuild: clean all

.PHONY: all clean rebuild