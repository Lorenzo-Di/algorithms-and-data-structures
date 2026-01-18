#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

/**
 * @file hash_table.h
 * @brief Generic chained hash table API.
 *
 * This library implements a hash table using separate chaining. Keys and
 * values are stored as generic pointers. Memory ownership of keys and values
 * remains with the user: the table stores them but never frees them.
 */

/**
 * @brief Opaque structure representing a hash table.
 */
typedef struct HashTable HashTable;

/**
 * @brief Create a new hash table.
 *
 * @param f1 Comparison function used to determine equality between keys.
 * The function must return 0 when the two keys are equal, and non‑zero
 * otherwise.
 * @param f2 Hash function applied to keys. It must return a 64‑bit hash
 * value and must be consistent: equal keys must produce identical hashes.
 *
 * @return Pointer to the newly allocated hash table, or NULL on failure.
 */
HashTable* hash_table_create(int (*f1)(const void*, const void*), unsigned long (*f2)(const void*));

/**
 * @brief Insert or overwrite a key‑value pair.
 *
 * If the key already exists, its value is replaced. Keys and values are not
 * copied; only their pointers are stored.
 *
 * @param table The hash table.
 * @param key Pointer to the key.
 * @param value Pointer to the value.
 */
void hash_table_put(HashTable* table, const void* key, const void* value);

/**
 * @brief Retrieve the value associated with a given key.
 *
 * @param table The hash table.
 * @param key The key to look up.
 *
 * @return Pointer to the associated value, or NULL if the key is absent.
 */
void* hash_table_get(const HashTable* table, const void* key);

/**
 * @brief Check whether the table contains the given key.
 *
 * @param table The hash table.
 * @param key The key to check.
 *
 * @return 1 if the key is present, 0 otherwise.
 */
int hash_table_contains_key(const HashTable* table, const void* key);

/**
 * @brief Remove a key‑value pair from the table.
 *
 * This does not free the key or value; it only removes the entry.
 *
 * @param table The hash table.
 * @param key The key to remove.
 */
void hash_table_remove(HashTable* table, const void* key);

/**
 * @brief Get the number of entries currently stored.
 *
 * @param table The hash table.
 * @return Number of stored key‑value pairs. -1 if the table is NULL
 *         or if the size exceeds INT_MAX.
 */
int hash_table_size(const HashTable* table);

/**
 * @brief Get the number of entries currently stored.
 * 
 * @param table The hash table.
 * @return Number of stored key-value pairs. 0 if the table is NULL.
 */
size_t hash_table_size_size_t(const HashTable *table);

/**
 * @brief Retrieve an array of all keys.
 *
 * Keys are not duplicated: the returned array contains the same pointers
 * stored internally. The user is responsible for freeing only the returned
 * array, not the keys.
 *
 * @param table The hash table.
 * @return A newly allocated array of key pointers. The array length equals the current table size.
 *         If the table is empty, the function returns a valid malloc(0) pointer (which must still be freed).
 *         Returns NULL if a memory allocation error occurs.
 */
void** hash_table_keyset(const HashTable* table);

/**
 * @brief Free the hash table structure.
 *
 * This frees all internal nodes and buckets but does **not** free keys or
 * values. The user must free them separately if needed.
 *
 * @param table The hash table.
 */
void hash_table_free(HashTable* table);

#endif /* HASH_TABLE_H */