#include "graph.h"
#include "hash_table.h"
#include <stdlib.h>
#include <limits.h>

struct graph
{
    HashTable* nodes;
    int is_labelled;
    int is_directed;
    int (*compare)(const void*, const void*);
    unsigned long (*hash)(const void*);
};

Graph graph_create(int labelled,
                  int directed,
                  int (*compare)(const void*, const void*),
                  unsigned long (*hash)(const void*)) {
    if(!(compare && hash)) { return NULL; }

    Graph gr = malloc(sizeof(struct graph));
    if(!gr) { return NULL; }

    if(labelled == 1) { gr->is_labelled = 1; }
    else { gr->is_labelled = 0; }

    if(directed == 1) { gr->is_directed = 1; }
    else { gr->is_directed = 0; }

    gr->compare = compare;
    gr->hash = hash;

    HashTable *nodes = hash_table_create(compare, hash);
    if(nodes) { gr->nodes = nodes; }
    else { free(gr); return NULL; }

    return gr;
}

int graph_is_directed(const Graph gr ) {
    if(!gr) { return 0; }
    return gr->is_directed;
}

int graph_is_labelled(const Graph gr) {
    if(!gr) { return 0; }
    return gr->is_labelled;
}

int graph_add_node(Graph gr, const void* node) {
    if(!(gr && node)) { return 0; }
    if(hash_table_contains_key(gr->nodes, node)) { return 0; }

    HashTable *adj = hash_table_create(gr->compare, gr->hash);
    if(!adj) { return 0; }
    hash_table_put(gr->nodes, node, adj);
    return 1;
}

int graph_contains_node(const Graph gr, const void* node) {
    if(!(gr && node)) { return 0; }
    return hash_table_contains_key(gr->nodes, node);
}

int graph_remove_node(Graph gr, const void* node) {
    int is_valid = graph_contains_node(gr, node);
    if(is_valid != 1) { return is_valid; }
    
    if(!gr->is_directed) {
        int nof_adjs = graph_num_neighbours(gr, node);
        if(nof_adjs > 0) {
            void **adjs = graph_get_neighbours(gr, node);
            if(!adjs) { return -1; } 

            for(int i = 0; i < nof_adjs; i++) {
                if(graph_remove_edge(gr, node, adjs[i]) == -1) {
                    free(adjs);
                    return -1;
                }
            }
            free(adjs);
        }
    }

    else { //gr->is_directed
        void **keys = graph_get_nodes(gr);
        if(!keys) { return -1; }

        int nof_nodes = graph_num_nodes(gr);
        for(int i=0; i < nof_nodes; i++) {
            if(graph_contains_edge(gr, keys[i], node) == 1) {
                graph_remove_edge(gr, keys[i], node);
            }
        }
        free(keys);
    }

    HashTable *node_table = hash_table_get(gr->nodes, node);
    if(!node_table) { return -1; }

    hash_table_free(node_table);
    hash_table_remove(gr->nodes, node);
    return 1;
}

int graph_num_nodes(const Graph gr) {
    return hash_table_size(gr->nodes);
}

void** graph_get_nodes(const Graph gr) {
    return hash_table_keyset(gr->nodes);
}

int graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label) {
    if(!(gr && node1 && node2 && (!gr->is_labelled || label))) { return 0; }
    if(graph_contains_edge(gr, node1, node2) == 1) { return 0; }
    
    HashTable *node1_table = hash_table_get(gr->nodes, node1);
    if(!node1_table) { return 0; }

    if(gr->is_labelled) { hash_table_put(node1_table, node2, label); }
    else { hash_table_put(node1_table, node2, NULL); }

    if(!gr->is_directed) {
        HashTable *node2_table = hash_table_get(gr->nodes, node2);
        if(!node2_table) { return 0; }

        if(gr->is_labelled) { hash_table_put(node2_table, node1, label); }
        else { hash_table_put(node2_table, node1, NULL); }
    }

    return 1;
}

int graph_contains_edge(const Graph gr, const void* node1, const void* node2) {
    if(!(gr && node1 && node2)) { return 0; }

    HashTable *node1_table = hash_table_get(gr->nodes, node1);
    if(!node1_table) { return 0; }

    if(hash_table_contains_key(node1_table, node2)) { return 1; }
    return 0;
}

int graph_remove_edge(Graph gr, const void* node1, const void* node2) {
    if(!(gr && node1 && node2)) { return -1; }
    if(graph_contains_edge(gr, node1, node2) == 0) { return 0; }

    HashTable *node1_table = hash_table_get(gr->nodes, node1);
    if(!node1_table) { return -1; }

    hash_table_remove(node1_table, node2);

    if(!gr->is_directed) {
        HashTable *node2_table = hash_table_get(gr->nodes, node2);
        if(!node2_table) { return -1; }

        hash_table_remove(node2_table, node1);
    }
    return 1;
}

int graph_num_edges(const Graph gr) {
    void **nodes = hash_table_keyset(gr->nodes);
    if(!nodes) { return 0; }
    int nof_nodes = hash_table_size(gr->nodes);

    size_t total_nof_edges = 0;
    int sing_nof_edges = 0;
    for(int i = 0; i < nof_nodes; i++) {
        if((sing_nof_edges = hash_table_size(hash_table_get(gr->nodes, nodes[i]))) == -1) { return 0; }
        total_nof_edges += (unsigned int)sing_nof_edges;
    }
    
    free(nodes);

    if(!gr->is_directed) { total_nof_edges /= 2; }
    if(total_nof_edges > INT_MAX) { return 0; }
    return (int)total_nof_edges;
}

Edge** graph_get_edges(const Graph gr) {
    if(!gr) { return NULL; }

    int nof_edges = graph_num_edges(gr);
    if(nof_edges <= 0) { return NULL; }

    Edge **edges = malloc(sizeof(Edge*) * (unsigned int)nof_edges);
    if(!edges) { return NULL; }

    for(int i = 0; i < nof_edges; i++) {
        edges[i] = malloc(sizeof(Edge));
        if(!edges[i]) {
            for(int j = 0; j < i; j++) { //this many mallocs could be avoided by just returning Edge* instead of Edge** and allocating all the memory needed for the array together
                free(edges[j]);
            }
            free(edges);
            return NULL;
        }
    }
    
    void **nodes = hash_table_keyset(gr->nodes);
    if(!nodes) { 
        for(int i = 0; i < nof_edges; i++) {
            free(edges[i]);
        }
        free(edges);
        return NULL; 
    }

    int nof_nodes = graph_num_nodes(gr);
    int edge_idx = 0;

    for(int i = 0; i < nof_nodes; i++) {
        void *curr_node = nodes[i];
        HashTable *adj = hash_table_get(gr->nodes, curr_node);
        
        int n_neighbors = hash_table_size(adj);
        if(n_neighbors <= 0) continue;

        void **node_edges = hash_table_keyset(adj);
        if(!node_edges) continue;

        for(int k = 0; k < n_neighbors; k++) {
            void *neighbor = node_edges[k];

            if(!gr->is_directed) {
                if(gr->compare(curr_node, neighbor) >= 0) { continue; }
            }

            if(edge_idx >= nof_edges) { continue; }

            edges[edge_idx]->source = curr_node;
            edges[edge_idx]->dest = neighbor;
            edges[edge_idx]->label = graph_get_label(gr, curr_node, neighbor);
            edge_idx++;
        }
        free(node_edges);
    }

    free(nodes);
    return edges;
}

void* graph_get_label(const Graph gr, const void* node1, const void* node2) {
    if(!(gr && node1 && node2 && gr->is_labelled)) { return NULL; }

    void *node_table = hash_table_get(gr->nodes, node1);
    if(!node_table) { return NULL; }
    return hash_table_get(node_table, node2);
}

void** graph_get_neighbours(const Graph gr, const void* node) {
    if(!(gr && node)) { return NULL; }

    void *node_table = hash_table_get(gr->nodes, node);
    if(!node_table) { return NULL; }
    return hash_table_keyset(node_table);
}

int graph_num_neighbours(const Graph gr, const void* node) {
    if(!(gr && node)) { return 0; }

    void *node_table = hash_table_get(gr->nodes, node);
    if(!node_table) { return 0; }
    return hash_table_size(node_table);
}

void graph_free(Graph gr) {
    if(!gr) { return; }
    
    void **nodes = hash_table_keyset(gr->nodes);
    if(!nodes) { return; }
    int nof_nodes = hash_table_size(gr->nodes);
    
    for(int i = 0; i < nof_nodes; i++) {
        HashTable *adj = hash_table_get(gr->nodes, nodes[i]);
        hash_table_free(adj);
    }
    free(nodes);

    hash_table_free(gr->nodes);

    free(gr);
}