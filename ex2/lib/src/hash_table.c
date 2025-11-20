#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

/* Internal node for chaining */
typedef struct HashNode {
    const void *key;
    const void *value;
    struct HashNode *next;
} HashNode;

/* Hash table structure */
struct HashTable {
    HashNode **buckets;
    size_t capacity;
    size_t size;
    int (*compare)(const void*, const void*);
    unsigned long (*hash)(const void*);
};

/* Default initial capacity (must be >0) */
static const size_t INITIAL_CAPACITY = 1024;

static int hash_table_resize(HashTable *table);

HashTable* hash_table_create(int (*f1)(const void*, const void*), unsigned long (*f2)(const void*)) {
    if (!f1 || !f2) {
        return NULL;
    }

    HashTable *table = malloc(sizeof(HashTable));
    if (!table) {
        return NULL;
    }

    table->capacity = INITIAL_CAPACITY;
    table->size = 0;
    table->compare = f1;
    table->hash = f2;

    table->buckets = calloc(table->capacity, sizeof(HashNode*));
    if (!table->buckets) {
        free(table);
        return NULL;
    }

    return table;
}