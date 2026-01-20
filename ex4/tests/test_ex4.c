#include "unity.h"
#include "graph.h"
#include <stdlib.h>
#include <string.h>

/* Global Static Variables (Data Fixtures) */

static Graph gr = NULL;

static int n1 = 1;
static int n2 = 2;
static int n3 = 3;
static int n10 = 10;
static int n20 = 20;

static char *s1 = "A";
static char *s2 = "B";
static char *label_road = "Road";

/* Helper Functions (Comparators & Hashers) */

static int compare_int(const void *a, const void *b) {
    int va = *(const int*)a;
    int vb = *(const int*)b;
    return (va > vb) - (va < vb);
}

static unsigned long hash_int(const void *a) {
    return (unsigned long)(*(const int*)a);
}

static int compare_str(const void *a, const void *b) {
    return strcmp((const char*)a, (const char*)b);
}

static unsigned long hash_str(const void *a) {
    unsigned long hash = 5381;
    int c;
    const char *str = (const char*)a;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + (unsigned int)c;
    return hash;
}

/* Setup & Teardown */

void setUp(void) {
    gr = NULL;
    n1 = 1; n2 = 2; n3 = 3; n10 = 10; n20 = 20;
}

void tearDown(void) {
    graph_free(gr);
}


void test_graph_create_invalid_input(void) {
    TEST_ASSERT_NULL(graph_create(0, 0, NULL, NULL));
    TEST_ASSERT_NULL(graph_create(0, 0, compare_int, NULL));
}

void test_graph_properties(void) {
    gr = graph_create(1, 1, compare_int, hash_int);
    TEST_ASSERT_NOT_NULL(gr);
    TEST_ASSERT_EQUAL_INT(1, graph_is_directed(gr));
    TEST_ASSERT_EQUAL_INT(1, graph_is_labelled(gr));
    
    TEST_ASSERT_EQUAL_INT(0, graph_is_directed(NULL));
    TEST_ASSERT_EQUAL_INT(0, graph_is_labelled(NULL));
}

void test_nodes_management(void) {
    gr = graph_create(0, 0, compare_int, hash_int);
    
    TEST_ASSERT_TRUE(graph_add_node(gr, &n10));
    TEST_ASSERT_TRUE(graph_add_node(gr, &n20));
    
    TEST_ASSERT_FALSE(graph_add_node(gr, &n10));
    
    TEST_ASSERT_TRUE(graph_contains_node(gr, &n10));
    TEST_ASSERT_FALSE(graph_contains_node(gr, (void*)&gr)); 
    TEST_ASSERT_EQUAL_INT(2, graph_num_nodes(gr));

    void **nodes = graph_get_nodes(gr);
    TEST_ASSERT_NOT_NULL(nodes);
    free(nodes);
}

void test_directed_graph_edges(void) {
    gr = graph_create(0, 1, compare_int, hash_int);
    
    graph_add_node(gr, &n1);
    graph_add_node(gr, &n2);

    TEST_ASSERT_TRUE(graph_add_edge(gr, &n1, &n2, NULL));
    TEST_ASSERT_FALSE(graph_add_edge(gr, &n1, &n2, NULL));

    // Verify Direction
    TEST_ASSERT_TRUE(graph_contains_edge(gr, &n1, &n2));
    TEST_ASSERT_FALSE(graph_contains_edge(gr, &n2, &n1));
    TEST_ASSERT_EQUAL_INT(1, graph_num_edges(gr));
    TEST_ASSERT_EQUAL_INT(1, graph_num_neighbours(gr, &n1));
    TEST_ASSERT_EQUAL_INT(0, graph_num_neighbours(gr, &n2));
}

void test_undirected_graph_edges(void) {
    gr = graph_create(0, 0, compare_int, hash_int);
    
    graph_add_node(gr, &n1);
    graph_add_node(gr, &n2);

    TEST_ASSERT_TRUE(graph_add_edge(gr, &n1, &n2, NULL));

    // Verify Symmetry
    TEST_ASSERT_TRUE(graph_contains_edge(gr, &n1, &n2));
    TEST_ASSERT_TRUE(graph_contains_edge(gr, &n2, &n1));
    
    TEST_ASSERT_EQUAL_INT(1, graph_num_edges(gr));
    
    TEST_ASSERT_EQUAL_INT(1, graph_num_neighbours(gr, &n1));
    TEST_ASSERT_EQUAL_INT(1, graph_num_neighbours(gr, &n2));
}

void test_remove_edge(void) {
    gr = graph_create(0, 0, compare_int, hash_int);
    
    graph_add_node(gr, &n1);
    graph_add_node(gr, &n2);
    graph_add_edge(gr, &n1, &n2, NULL);

    TEST_ASSERT_TRUE(graph_remove_edge(gr, &n1, &n2));
    TEST_ASSERT_FALSE(graph_contains_edge(gr, &n1, &n2));
    TEST_ASSERT_FALSE(graph_contains_edge(gr, &n2, &n1));
    TEST_ASSERT_EQUAL_INT(0, graph_num_edges(gr));
    
    TEST_ASSERT_FALSE(graph_remove_edge(gr, &n1, &n2)); 
}

void test_remove_node_and_incident_edges_undirected(void) {
    gr = graph_create(0, 0, compare_int, hash_int);
    
    graph_add_node(gr, &n1);
    graph_add_node(gr, &n2);
    graph_add_edge(gr, &n1, &n2, NULL);

    TEST_ASSERT_TRUE(graph_remove_node(gr, &n1));
    
    TEST_ASSERT_EQUAL_INT(1, graph_num_nodes(gr));
    TEST_ASSERT_FALSE(graph_contains_node(gr, &n1));
    TEST_ASSERT_EQUAL_INT(0, graph_num_neighbours(gr, &n2)); 
}

void test_remove_node_and_incident_edges_directed(void) {
    gr = graph_create(0, 1, compare_int, hash_int);
    
    graph_add_node(gr, &n1);
    graph_add_node(gr, &n2);
    graph_add_edge(gr, &n1, &n2, NULL);

    TEST_ASSERT_TRUE(graph_remove_node(gr, &n2));
    
    TEST_ASSERT_EQUAL_INT(1, graph_num_nodes(gr));
    TEST_ASSERT_EQUAL_INT(0, graph_num_neighbours(gr, &n1)); 
}

void test_labelled_edges(void) {
    gr = graph_create(1, 1, compare_str, hash_str);
    
    graph_add_node(gr, s1);
    graph_add_node(gr, s2);
    graph_add_edge(gr, s1, s2, label_road);
    
    char *retrieved = (char*)graph_get_label(gr, s1, s2);
    TEST_ASSERT_EQUAL_STRING(label_road, retrieved);
    TEST_ASSERT_NULL(graph_get_label(gr, s2, s1)); 
}

void test_graph_get_edges_array_structure(void) {
    gr = graph_create(0, 0, compare_int, hash_int);
    
    graph_add_node(gr, &n1);
    graph_add_node(gr, &n2);
    graph_add_node(gr, &n3);
    
    graph_add_edge(gr, &n1, &n2, NULL);
    graph_add_edge(gr, &n2, &n3, NULL);

    Edge **edges = graph_get_edges(gr);
    TEST_ASSERT_NOT_NULL(edges);
    
    TEST_ASSERT_NOT_NULL(edges[0]->source);
    TEST_ASSERT_NOT_NULL(edges[1]->source);
    
    free(edges[0]); 
    free(edges[1]);
    free(edges); 
}

void test_null_inputs(void) {
    gr = graph_create(0, 0, compare_int, hash_int);
    
    TEST_ASSERT_EQUAL_INT(0, graph_add_node(NULL, &n1));
    TEST_ASSERT_EQUAL_INT(0, graph_add_node(gr, NULL));
    TEST_ASSERT_EQUAL_INT(0, graph_remove_node(NULL, &n1));
    TEST_ASSERT_NULL(graph_get_neighbours(NULL, &n1));
    TEST_ASSERT_EQUAL_INT(0, graph_num_edges(NULL));
    
    graph_free(NULL);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_graph_create_invalid_input);
    RUN_TEST(test_graph_properties);
    RUN_TEST(test_nodes_management);
    RUN_TEST(test_directed_graph_edges);
    RUN_TEST(test_undirected_graph_edges);
    RUN_TEST(test_remove_edge);
    RUN_TEST(test_remove_node_and_incident_edges_undirected);
    RUN_TEST(test_remove_node_and_incident_edges_directed);
    RUN_TEST(test_labelled_edges);
    RUN_TEST(test_graph_get_edges_array_structure);
    RUN_TEST(test_null_inputs);

    return UNITY_END();
}