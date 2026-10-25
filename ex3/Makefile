CC = gcc
INCLUDES = -Iinclude -Itests/unity
CFLAGS = -g $(INCLUDES) -Wall -Wextra -Wpedantic -Wconversion

SRC = $(filter-out src/main.c, $(wildcard src/*.c))
OBJ = $(patsubst src/%.c, build/src/%.o, $(SRC))

all: bin/main_ex3 bin/test_ex3

bin/main_ex3: $(OBJ) build/src/main.o
	$(CC) $(CFLAGS) $^ -o $@

bin/test_ex3: $(OBJ) build/tests/unity/unity.o build/tests/test_ex3.o
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: %.c folders
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

folders:
	@mkdir -p build/ bin/

clean:
	@rm -rf build/ bin/

rebuild: clean all

.PHONY: all clean rebuild folders