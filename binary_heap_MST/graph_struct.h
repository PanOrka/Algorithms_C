typedef struct list list;
typedef struct vertice vertice;

/*
// List structure, with weight (edge from vertice)
*/
struct list {
    list *next;
    double weight;
    int v;
};

/*
// Vertice structure
*/
struct vertice {
    list *n;
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
