#include "binary_heap.h"
#include "binary_heap_2.h"

typedef struct mst mst;

/*
// List for edges
*/
struct mst {
    double weight;
    int u, v;
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
void prim_mst(graph *g, int start);

/*
// Kruskal's algorithm (MST)
*/
void kruskal_mst(graph_2 *g);
