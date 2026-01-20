#ifndef BFS_H
#define BFS_H

#include "graph.h"
/**
 * @mainpage Algorithm project Documentation
 *
 * @section intro_sec Introduction
 * This is the documentation for a breadth first visit library.
 *
 * @section usage_sec How to use
 * Include bfs.h and graph.h.
 * Create the graph and add the nodes and edges using the functions in graph.h
 * Then call breadth_first_visit() on the created graph.
 */

/**
 * @file bfs.h
 * @brief Generic Breadth First Visit API.
 * 
 * This library implements a bfs of a graph using a queue and various hash tables.
 */

/**
 * @brief Standard visit using bfs.
 * 
 * @param gr The graph to visit.
 * @param start The starting node.
 * @param compar Comparison function used to determine order and equality between elements.
 * The function returns an integer less than, equal to, or greater than zero if the first
 * argument is considered to be respectively less than, equal to, or greater than the second.
 * @param hash_func Hash function for hash table used as support to esnure less than linear complexity.
 * It must return a 64‑bit hash value and must be consistent: equal keys must produce
 * identical hashes.
 * 
 * @return A newly allocated array with all the nodes in order of visit.
 */
void** breadth_first_visit(Graph gr,
                          void* start,
                          int (*compare)(const void*, const void*),
                          unsigned long (*hash)(const void*));

#endif /* BFS_H */