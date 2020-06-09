#include "graph_struct.h"

/*
// Node structure
*/
typedef struct {
    int value;
} node;

/*
// Heap structure
*/
typedef struct {
    node *tab;
    graph *g;
    int used_size, max_size;
} heap;

/*
// Creating binary-heap
*/
heap * create_heap(graph *g);

/*
// Inserting whole graph to binary-heap
*/
void insert_all(heap *h, int start);

/*
// Checking whether heap is empty, returns 1 if is empty, else 0
*/
int is_empty(heap *h);

/*
// Return highest prior node value and delete it, if doesn't exist print blank line
*/
node pop(heap *h);

/*
// Increased priority call of i-th element
*/
void decrease_distance(heap *h, int i);
