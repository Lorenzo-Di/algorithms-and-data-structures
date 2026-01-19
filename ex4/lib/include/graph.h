#ifndef GRAPH_H
#define GRAPH_H

/**
 * @file graph.h
 * @brief Generic graph API.
 *
 * This library implements a graph using hash tables instead of adjency lists.
 * Memory ownerhip of the elements stays with the user. The graph stores the pointers
 * but never frees them.
 */

/**
 * @brief Opaque structure representing a graph.
 */
typedef struct graph *Graph;

/**
 * @brief Struct representing a graph's edge.
 * 
 * @param source Source node.
 * @param dest Destination node.
 * @param label Edge's label.
 */
typedef struct edge {
    void* source;
    void* dest;
    void* label;
} Edge;

/**
 * @brief Creates a new graph.
 * 
 * @param labelled Should be 1 if the graph needs to be labelled.
 * @param directed Should be 1 if the graph needs to be directed.
 * @param compar Comparison function used to determine equality between elements.
 * The function returns 0 when the two keys are equal, and non‑zero
 * otherwise.
 * @param hash_func Hash function for hash table used as support to esnure less than linear complexity.
 * It must return a 64‑bit hash value and must be consistent: equal keys must produce
 * identical hashes.
 * 
 * @return A pointer to the created graph, NULL on failure.
 */
Graph graph_create(int labelled,
                  int directed,
                  int (*compare)(const void*, const void*),
                  unsigned long (*hash)(const void*));

/**
 * @brief Check if a graph is directed.
 * 
 * @param gr The graph.
 * @return 1 if directed, 0 if undirected, -1 on failure.
 */
int graph_is_directed(const Graph gr);

/**
 * @brief Check if a graph is labelled.
 * 
 * @param gr The graph.
 * @return 1 if labelled, 0 if unlabelled, -1 on failure.
 */
int graph_is_labelled(const Graph gr);

/**
 * @brief Adds a node to the graph.
 * 
 * @param gr The graph.
 * @param node The node to add.
 * @return 1 on success, 0 if the node is already present, -1 on failure.
 */
int graph_add_node(Graph gr, const void* node);

/**
 * @brief Checks if a node is in the graph.
 * 
 * @param gr The graph.
 * @param node The node to find.
 * @return 1 if the node is present, 0 if it's not present, -1 on failure.
 */
int graph_contains_node(const Graph gr, const void* node);

/**
 * @brief Removes a node from the graph.
 * 
 * @param gr The graph.
 * @param node The node to remove.
 * @return 1 if the node was removed correctly, 0 if the node is not present, -1 on failure.
 */
int graph_remove_node(Graph gr, const void* node);

/**
 * @brief Get the numbers of nodes currently stored.
 * 
 * @param gr The graph.
 * @return -1 on failure, the number of nodes otherwise.
 */
int graph_num_nodes(const Graph gr);

/**
 * @brief Retrieve an array of all nodes.
 *
 * Nodes are not duplicated: the returned array contains the same pointers
 * stored internally. The user is responsible for freeing only the returned
 * array, not the nodes.
 *
 * @param gr The graph.
 * @return A newly allocated array of node pointers. The array length equals the current graph size.
 *         If the graph is empty, the function returns a valid malloc(0) pointer (which must still be freed).
 *         Returns NULL if a memory allocation error occurs.
 */
void** graph_get_nodes(const Graph gr);

/**
 * @brief Adds an edge to the graph.
 * 
 * @param gr The graph.
 * @param node1 The source node.
 * @param node2 The destination node.
 * @param label The label of the edge. This is ignored if the graph is not labelled.
 * 
 * @return 1 on success, 0 if the edge was already present, -1 failure.
 */
int graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label);

/**
 * @brief Checks if an edge is present in the graph.
 * 
 * @param gr The graph.
 * @param node1 The source node.
 * @param node2 The destination node.
 * @return 1 if the edge is present, 0 if it is not, -1 on failure.
 */
int graph_contains_edge(const Graph gr, const void* node1, const void* node2);

/**
 * @brief Removes an edge from the graph.
 * 
 * @param gr The graph.
 * @param node1 The source node.
 * @param node2 The destination node.
 * @return 1 if removed successfully, 0 if the edge is not present, -1 on failure. 
 */
int graph_remove_edge(Graph gr, const void* node1, const void* node2);

/**
 * @brief Get the number of edges currently stored.
 * 
 * @param gr The graph.
 * @return -1 on failure or if the number of edges > INT_MAX, the number of edges otherwise.
 */
int graph_num_edges(const Graph gr);

/**
 * @brief Retrieve an array of all edges.
 *
 * The returned array contains the pointers to newly allocated edge structs.
 * The user is responsible for freeing both the returned array and the single
 * edge structs.
 *
 * @param gr The graph.
 * @return A newly allocated array of edge pointers. The array length equals the current number of edges.
 *         If the graph is empty, the function returns a valid malloc(0) pointer (which must still be freed).
 *         Returns NULL if a memory allocation error occurs.
 */
Edge** graph_get_edges(const Graph gr);

/**
 * @brief Retrieve the label of an edge.
 * 
 * @param gr The labelled graph.
 * @param node1 The source node.
 * @param node2 The destination node.
 * @return the label of the edge, NULL if the graph is not labelled or failure
 */
void* graph_get_label(const Graph gr, const void* node1, const void* node2);

/**
 * @brief Retrieve an array of all nodes adjacent to the given node.
 *
 * Nodes are not duplicated: the returned array contains the same pointers
 * stored internally. The user is responsible for freeing only the returned
 * array, not the nodes.
 *
 * @param gr The graph.
 * @param node The source node.
 * @return A newly allocated array of node pointers. The array length equals the number of neighbours of the node.
 *         If the graph is empty, the function returns a valid malloc(0) pointer (which must still be freed).
 *         Returns NULL if a memory allocation error occurs.
 */
void** graph_get_neighbours(const Graph gr, const void* node);

/**
 * @brief Get the number of nodes adjacent to the given node.
 * 
 * @param gr The graph.
 * @param node The source node.
 * @return The number of neighbours of the node, -1 if the number of neighbours > INT_MAX or failure.
 */
int graph_num_neighbours(const Graph gr, const void* node);

/**
 * @brief Free the graph structure.
 *
 * This frees all supporting structures and edges but does **not** free the nodes.
 * The user must free them separately if needed.
 *
 * @param table The hash table.
 */
void graph_free(Graph gr);

#endif /* GRAPH_H */