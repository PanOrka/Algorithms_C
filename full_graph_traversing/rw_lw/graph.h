#include <stdbool.h>

typedef struct vertice_rw vertice_rw;
typedef struct edge_rw edge_rw;

/*
// Structure of edge, with weight
*/
struct edge_rw {
    double weight;
};

/*
// Vertice with was_explored flag and array of neighbours,
// graph is full so it doesn't have to be list, we have v_size-1
// edges from every vertice.
*/
struct vertice_rw {
    edge_rw *n; // neighbours
    bool was_explored;
};

/*
// Graph with vertice_rw array
*/
typedef struct {
    vertice_rw *vertices;
    int v_size;
} graph_rw;

/*
// Creating new rw graph with v_size vertices
*/
graph_rw * create_graph_rw(int v_size);

/*
// Traversing graph randomly.
*/
void traverse_rw(graph_rw *g);

/*
// Traversing graph choosing lowest weight.
*/
void traverse_lw(graph_rw *g);

/*
// Clear was_explored flag
*/
void clear_flag_rw(graph_rw *g);

//TEMP
void graph_rw_take_stdin(graph_rw *g);
