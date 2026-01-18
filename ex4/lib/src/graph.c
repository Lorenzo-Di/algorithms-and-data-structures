#include "graph.h"
#include "hash_table.h"
#include <stdlib.h>

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

int graph_is_directed(const Graph gr){
    if(!gr) { return -1; }
    return gr->is_directed;
}

int graph_is_labelled(const Graph gr){
    if(!gr) { return -1; }
    return gr->is_labelled;
}
