#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash_table.h"

#define MAX_WORD_LEN 256

/* --- Hash Table Helper Functions --- */

/* Wrapper for strcmp (conforms to hash table comparison signature) */
static int compare_strings(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

/* DJB2 hash algorithm (excellent for strings) */
static unsigned long hash_string(const void* k) {
    unsigned long hash = 5381;
    int c;
    const char *str = (const char*)k;

    while ((c = *str++)) {
        /* Cast to unsigned long to satisfy -Wsign-conversion */
        hash = ((hash << 5) + hash) + (unsigned long)c; /* hash * 33 + c */
    }
    return hash;
}

/* --- Utility Functions --- */

/* * Cleans the word: keeps only alphabetic characters and converts to lowercase.
 * Returns 1 if the word is valid (length > 0), 0 otherwise.
 */
static int clean_word(char* dest, const char* src) {
    int pos = 0;
    while (*src) {
        if (isalpha((unsigned char)*src)) {
            if (pos < MAX_WORD_LEN - 1) {
                dest[pos++] = (char)tolower((unsigned char)*src);
            }
        }
        src++;
    }
    dest[pos] = '\0';
    return pos > 0;
}

/* Duplicates a string (safe implementation for strict C99) */
static char* strdup_safe(const char* s) {
    size_t len = strlen(s) + 1;
    char* new_s = malloc(len);
    if (new_s) {
        memcpy(new_s, s, len);
    }
    return new_s;
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

    char raw_buffer[MAX_WORD_LEN];
    char clean_buffer[MAX_WORD_LEN];

    /* Read file word by word */
    while (fscanf(fp, "%255s", raw_buffer) == 1) {
        if (clean_word(clean_buffer, raw_buffer)) {
            if (strlen(clean_buffer) >= min_len) {
                
                /* Check if word already exists */
                int* count = (int*)hash_table_get(table, clean_buffer);
                
                if (count) {
                    /* If exists, increment counter */
                    (*count)++;
                } else {
                    /* If not, allocate key and value */
                    char* key = strdup_safe(clean_buffer);
                    int* val = malloc(sizeof(int));
                    
                    if (key && val) {
                        *val = 1;
                        hash_table_put(table, key, val);
                    } else {
                        /* Handle allocation error */
                        free(key); /* free handles NULL */
                        free(val);
                    }
                }
            }
        }
    }
    
    fclose(fp);

    /* --- Result Analysis --- */
    
    char* most_freq_word = NULL;
    int max_freq = 0;

    /* Get all keys to iterate */
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

    /* Required Output */
    if (most_freq_word) {
        printf("Most frequent word (len >= %zu): %s (%d times)\n", 
               min_len, most_freq_word, max_freq);
    } else {
        printf("No words found with length >= %zu.\n", min_len);
    }

    /* --- Cleanup --- */
    /* Important: The table does not free keys and values, we must do it manually.
       We use the keys array we already retrieved. */
    
    if (keys) {
        for (int i = 0; i < size; i++) {
            char* key = (char*)keys[i];
            int* val = (int*)hash_table_get(table, key);
            
            free(key); /* Free duplicated string */
            free(val); /* Free int counter */
        }
        free(keys); /* Free keys array */
    }

    hash_table_free(table); /* Free table structure */

    return EXIT_SUCCESS;
}