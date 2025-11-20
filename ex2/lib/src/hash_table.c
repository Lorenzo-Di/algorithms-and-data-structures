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

void hash_table_put(HashTable* table, const void* key, const void* value) {
    if (!table || !key) {
        return;
    }

    unsigned long h = table->hash(key);
    size_t index = h % table->capacity;

    HashNode *node = table->buckets[index];

    /* Check if key already exists: overwrite */
    while (node) {
        if (table->compare(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }

    /* Insert new node at head of chain */
    HashNode *new_node = malloc(sizeof(HashNode));
    if (!new_node) {
        return; /* Allocation failure: leave table unchanged */
    }

    new_node->key = key;
    new_node->value = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;

    table->size++;

    double load = (double)table->size / (double)table->capacity;
    if (load > 0.75) {
        hash_table_resize(table);
    }
}

static int hash_table_resize(HashTable *table) {
    size_t new_capacity = table->capacity * 2;
    HashNode **new_buckets = calloc(new_capacity, sizeof(HashNode*));
    if (!new_buckets) {
        return 0;
    }

    for (size_t i = 0; i < table->capacity; i++) {
        HashNode *node = table->buckets[i];
        while (node) {
            HashNode *next = node->next;
            unsigned long h = table->hash(node->key);
            size_t new_index = h % new_capacity;
            node->next = new_buckets[new_index];
            new_buckets[new_index] = node;
            node = next;
        }
    }

    free(table->buckets);
    table->buckets = new_buckets;
    table->capacity = new_capacity;
    return 1;
}