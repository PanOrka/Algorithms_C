#include "graph_struct_2.h"

/*
// Node structure
*/
typedef struct {
    int value;
} node_2;

/*
// Heap structure
*/
typedef struct {
    node_2 *tab;
    graph_2 *g;
    int used_size, max_size;
} heap_2;

/*
// Creating binary-heap
*/
heap_2 * create_heap_2(graph_2 *g);

/*
// Inserting whole graph to binary-heap
*/
void insert_all_2(heap_2 *h);

/*
// Checking whether heap is empty, returns 1 if is empty, else 0
*/
int is_empty_2(heap_2 *h);

/*
// Return highest prior node value and delete it, if doesn't exist print blank line
*/
node_2 pop_2(heap_2 *h);

/*
// Increased priority call of i-th element
*/
void decrease_distance_2(heap_2 *h, int i);
