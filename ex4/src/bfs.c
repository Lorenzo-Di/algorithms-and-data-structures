#include "bfs.h"
#include "graph.h"
#include "queue.h"
#include "hash_table.h"
#include <stdlib.h>

void** breadth_first_visit(Graph gr,
                           void* start,
                           int (*compare)(const void*, const void*),
                           unsigned long (*hash)(const void*)) {
    
    if(!(gr && start && compare && hash)) { return NULL; }
    if(!graph_contains_node(gr, start)) { return NULL; }

    int num_nodes = graph_num_nodes(gr);
    if(num_nodes < 0) { return NULL; }
    void **result = malloc((unsigned int)(num_nodes + 1) * sizeof(void*)); //keep a space for terminating NULL to indicate end of array
    if(!result) { return NULL; }

    Queue to_visit = queue_create();
    HashTable *visited = hash_table_create(compare, hash);

    if(!(to_visit && visited)) {
        free(result);
        if(to_visit) { queue_free(to_visit); }
        if(visited) { hash_table_free(visited); }
        return NULL;
    }

    hash_table_put(visited, start, NULL);
    queue_enqueue(to_visit, start);

    unsigned int count = 0;

    while(!queue_is_empty(to_visit)) {
        void *current;
        if(!queue_dequeue(to_visit, &current)) { continue; }
            
        result[count++] = current;

        int num_neigh = graph_num_neighbours(gr, current);
        if(!num_neigh) { continue; }

        void **neighbours = graph_get_neighbours(gr, current);
        if(!neighbours) { continue; }

        for(int i = 0; i < num_neigh; i++) {
            void *neighbour = neighbours[i];

            if(!hash_table_contains_key(visited, neighbour)) {
                hash_table_put(visited, neighbour, NULL);
                queue_enqueue(to_visit, neighbour);
            }
        }
        free(neighbours);
    }

    queue_free(to_visit);
    hash_table_free(visited);
    
    result[count] = NULL; //string-like NULL-terminated array

    void **opt_result = realloc(result, (count + 1) * sizeof(void*));
    if(opt_result) { result = opt_result; }

    return result;
}