CC = gcc
# Flag comuni (C99 standard, simboli di debug)
COMMON_FLAGS = -std=c99 -g

# Flag restrittivi per il codice del progetto (Come richiesto)
STRICT_FLAGS = -Wall -Wextra -Wpedantic -Wconversion -Werror

# Directory
BIN_DIR = bin
BUILD_DIR = build
SRC_DIR = src
TEST_DIR = tests
LIB_DIR = lib
LIB_SRC = $(LIB_DIR)/src
LIB_INC = $(LIB_DIR)/include
UNITY_DIR = $(LIB_DIR)/unity

# Include paths
INCLUDES = -I$(LIB_INC) -I$(UNITY_DIR)

# Target finali
TARGET_MAIN = $(BIN_DIR)/main_ex2
TARGET_TEST = $(BIN_DIR)/test_ex2

# Oggetti
OBJ_HASH = $(BUILD_DIR)/hash_table.o
OBJ_UNITY = $(BUILD_DIR)/unity.o
OBJ_MAIN = $(BUILD_DIR)/main_ex2.o
OBJ_TEST = $(BUILD_DIR)/test_ex2.o

# Regola di default
all: directories $(TARGET_MAIN) $(TARGET_TEST)

# Creazione cartelle di output se non esistono
directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BUILD_DIR)

# --- Linker ---

# Crea l'eseguibile principale
$(TARGET_MAIN): $(OBJ_MAIN) $(OBJ_HASH)
	$(CC) $(COMMON_FLAGS) $(STRICT_FLAGS) -o $@ $^

# Crea l'eseguibile di test (include Unity)
$(TARGET_TEST): $(OBJ_TEST) $(OBJ_HASH) $(OBJ_UNITY)
	$(CC) $(COMMON_FLAGS) $(STRICT_FLAGS) -o $@ $^

# --- Compilazione ---

# Compila la libreria hash_table (con flag restrittivi)
$(OBJ_HASH): $(LIB_SRC)/hash_table.c
	$(CC) -c $(COMMON_FLAGS) $(STRICT_FLAGS) $(INCLUDES) $< -o $@

# Compila il main (con flag restrittivi)
$(OBJ_MAIN): $(SRC_DIR)/main_ex2.c
	$(CC) -c $(COMMON_FLAGS) $(STRICT_FLAGS) $(INCLUDES) $< -o $@

# Compila i test (con flag restrittivi)
$(OBJ_TEST): $(TEST_DIR)/test_ex2.c
	$(CC) -c $(COMMON_FLAGS) $(STRICT_FLAGS) $(INCLUDES) $< -o $@

# Compila Unity (SENZA flag restrittivi: è codice esterno)
$(OBJ_UNITY): $(UNITY_DIR)/unity.c
	$(CC) -c $(COMMON_FLAGS) $(INCLUDES) $< -o $@

# Pulizia
clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

.PHONY: all clean directories