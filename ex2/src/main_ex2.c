#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash_table.h"

#define MAX_WORD_LEN 256

/* --- Hash Table Helper Functions --- */

/* Wrapper for strcmp */
static int compare_strings(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

/* DJB2 hash algorithm */
static unsigned long hash_string(const void* k) {
    unsigned long hash = 5381;
    int c;
    const char *str = (const char*)k;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + (unsigned long)c;
    }
    return hash;
}

/* --- Utility Functions --- */

/* Duplicates a string (safe implementation) */
static char* strdup_safe(const char* s) {
    size_t len = strlen(s) + 1;
    char* new_s = malloc(len);
    if (new_s) {
        memcpy(new_s, s, len);
    }
    return new_s;
}

/* Helper to process a completed word */
static void process_word(HashTable* table, const char* buffer, size_t min_len) {
    if (strlen(buffer) >= min_len) {
        /* Check if word already exists */
        int* count = (int*)hash_table_get(table, buffer);
        
        if (count) {
            (*count)++;
        } else {
            char* key = strdup_safe(buffer);
            int* val = malloc(sizeof(int));
            
            if (key && val) {
                *val = 1;
                hash_table_put(table, key, val);
            } else {
                free(key);
                free(val);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <min_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    long min_len_arg = strtol(argv[2], NULL, 10);
    
    if (min_len_arg < 0) {
        fprintf(stderr, "Error: min_length must be non-negative.\n");
        return EXIT_FAILURE;
    }
    size_t min_len = (size_t)min_len_arg;

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    /* Create Hash Table */
    HashTable* table = hash_table_create(compare_strings, hash_string);
    if (!table) {
        fprintf(stderr, "Error: Failed to create hash table.\n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    /* Read character by character. 
       Punctuation (like '-') now acts as a separator, not just spaces. */
    
    char buffer[MAX_WORD_LEN];
    int pos = 0;
    int c;

    while ((c = fgetc(fp)) != EOF) {
        if (isalpha(c)) {
            /* If it's a letter, append to buffer */
            if (pos < MAX_WORD_LEN - 1) {
                buffer[pos++] = (char)tolower(c);
            }
        } else {
            /* If it's NOT a letter (space, punctuation, newline, hyphen),
               the current word (if any) is finished. */
            if (pos > 0) {
                buffer[pos] = '\0'; /* Terminate string */
                process_word(table, buffer, min_len);
                pos = 0; /* Reset buffer for next word */
            }
        }
    }
    
    /* Handle the very last word if file ends without newline/punctuation */
    if (pos > 0) {
        buffer[pos] = '\0';
        process_word(table, buffer, min_len);
    }

    fclose(fp);

    /* --- Result Analysis --- */
    
    char* most_freq_word = NULL;
    int max_freq = 0;

    void** keys = hash_table_keyset(table);
    int size = hash_table_size(table);

    if (keys && size > 0) {
        for (int i = 0; i < size; i++) {
            char* key = (char*)keys[i];
            int* val = (int*)hash_table_get(table, key);
            
            if (val && *val > max_freq) {
                max_freq = *val;
                most_freq_word = key;
            }
        }
    }

    if (most_freq_word) {
        printf("Most frequent word (len >= %zu): %s (%d times)\n", 
               min_len, most_freq_word, max_freq);
    } else {
        printf("No words found with length >= %zu.\n", min_len);
    }

    /* --- Cleanup --- */
    if (keys) {
        for (int i = 0; i < size; i++) {
            char* key = (char*)keys[i];
            int* val = (int*)hash_table_get(table, key);
            free(key);
            free(val);
        }
        free(keys);
    }

    hash_table_free(table);

    return EXIT_SUCCESS;
}