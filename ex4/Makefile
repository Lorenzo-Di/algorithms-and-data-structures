CC = gcc
INCLUDES = -Iinclude -Ilib/include -Itests/unity
CFLAGS = -g $(INCLUDES) -Wall -Wextra -Wpedantic -Wconversion

SRC = $(wildcard lib/src/*.c) $(filter-out src/main.c, $(wildcard src/*.c))
OBJ = $(patsubst %.c, build/%.o, $(SRC))

all: bin/main_ex4 bin/test_ex4

bin/main_ex4: $(OBJ) build/src/main.o
	$(CC) $(CFLAGS) $^ -o $@

bin/test_ex4: $(OBJ) build/tests/unity/unity.o build/tests/test_ex4.o
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: %.c folders
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

folders:
	@mkdir -p build/ bin/

clean:
	rm -rf build/ bin/

rebuild: clean all

.PHONY: all clean rebuild folders