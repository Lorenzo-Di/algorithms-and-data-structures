CC = gcc
INCLUDES = -Iinclude -Iinclude/utils -Ilib/include
CFLAGS = -g $(INCLUDES) -Wall -Wextra -Wpedantic -Wconversion

SRC = $(filter-out src/main.c, \
	  $(wildcard src/*.c) \
	  $(wildcard src/utils/*.c) \
	  $(wildcard lib/src/*.c))

OBJ = $(patsubst %.c, build/%.o, $(SRC))

all: bin/main_ex1 bin/test_ex1

bin/main_ex1: $(OBJ) build/src/main.o
	$(CC) $(CFLAGS) $^ -o $@

bin/test_ex1: $(OBJ) build/tests/test_ex1.o build/tests/unity.o
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: %.c folders
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

folders:
	mkdir -p build/ bin/

clean:
	rm -rf build/ bin/

rebuild: clean all
