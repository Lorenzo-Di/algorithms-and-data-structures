CC = gcc
COMMON_FLAGS = -std=c99 -g

STRICT_FLAGS = -Wall -Wextra -Wpedantic -Wconversion -Werror

BIN_DIR = bin
BUILD_DIR = build
SRC_DIR = src
TEST_DIR = tests
LIB_DIR = lib
LIB_SRC = $(LIB_DIR)/src
LIB_INC = $(LIB_DIR)/include
UNITY_DIR = $(LIB_DIR)/unity

INCLUDES = -I$(LIB_INC) -I$(UNITY_DIR)

TARGET_MAIN = $(BIN_DIR)/main_ex2
TARGET_TEST = $(BIN_DIR)/test_ex2

OBJ_HASH = $(BUILD_DIR)/hash_table.o
OBJ_UNITY = $(BUILD_DIR)/unity.o
OBJ_MAIN = $(BUILD_DIR)/main_ex2.o
OBJ_TEST = $(BUILD_DIR)/test_ex2.o

all: directories $(TARGET_MAIN) $(TARGET_TEST)

directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BUILD_DIR)


$(TARGET_MAIN): $(OBJ_MAIN) $(OBJ_HASH)
	$(CC) $(COMMON_FLAGS) $(STRICT_FLAGS) -o $@ $^

$(TARGET_TEST): $(OBJ_TEST) $(OBJ_HASH) $(OBJ_UNITY)
	$(CC) $(COMMON_FLAGS) $(STRICT_FLAGS) -o $@ $^


$(OBJ_HASH): $(LIB_SRC)/hash_table.c
	$(CC) -c $(COMMON_FLAGS) $(STRICT_FLAGS) $(INCLUDES) $< -o $@

$(OBJ_MAIN): $(SRC_DIR)/main_ex2.c
	$(CC) -c $(COMMON_FLAGS) $(STRICT_FLAGS) $(INCLUDES) $< -o $@

$(OBJ_TEST): $(TEST_DIR)/test_ex2.c
	$(CC) -c $(COMMON_FLAGS) $(STRICT_FLAGS) $(INCLUDES) $< -o $@

$(OBJ_UNITY): $(UNITY_DIR)/unity.c
	$(CC) -c $(COMMON_FLAGS) $(INCLUDES) $< -o $@

clean:
	@rm -rf $(BIN_DIR) $(BUILD_DIR)

.PHONY: all clean directories