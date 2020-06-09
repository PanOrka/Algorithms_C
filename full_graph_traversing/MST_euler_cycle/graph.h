#include <stdbool.h>

#include "binary_heap.h"
#include "binary_heap_2.h"

typedef struct mst mst;
typedef struct e_lst e_lst;

/*
// List of edges to traverse from node
*/
struct e_lst {
    e_lst *next;
    double weight;
    int v;
};

/*
// Vertice_mst structure
*/
typedef struct {
    e_lst *n;
    bool was_explored;
} vertice_mst;

/*
// List for edges
*/
struct mst {
    vertice_mst *vertices;
};

/*
// Graph creator
*/
graph * create_graph(int v_size, int e_size);

/*
// Graph creator for Kruskal
*/
graph_2 * create_graph_2(int v_size, int e_size);

/*
// Prim's algorithm (MST)
*/
mst * prim_mst(graph *g, int start);

/*
// Kruskal's algorithm (MST)
*/
mst * kruskal_mst(graph_2 *g);
