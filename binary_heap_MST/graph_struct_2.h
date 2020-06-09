/*
// Edge structure with weight (just for kruskal graph and different heap)
*/
typedef struct {
    double weight;
    int heap_place, u, v;
} edge;


/*
// Kruskal graph structure
*/
typedef struct {
    edge *edges;
    int v_size, e_size;
} graph_2;
