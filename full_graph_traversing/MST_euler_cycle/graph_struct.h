typedef struct vertice vertice;

/*
// List structure, with weight (edge from vertice)
*/
typedef struct {
    double weight;
    int v;
} neighbours;

/*
// Vertice structure
*/
struct vertice {
    neighbours *n;
    double dist;
    int heap_place, prev;
};

/*
// Graph structure
*/
typedef struct {
    vertice *vertices;
    int v_size, e_size;
} graph;
