/*
// Structure of subset
*/
typedef struct {
    int parent, rank;
} subset;

/*
// Find element with path compression
*/
int find(subset *sub, int i);

/*
// Union of subsets
*/
void union_of_subsets(subset *sub, int x_root, int y_root);
