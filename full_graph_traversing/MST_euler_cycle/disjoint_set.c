#include "disjoint_set.h"

int find(subset *sub, int i) {
    if (sub[i].parent != i) {
        sub[i].parent = find(sub, sub[i].parent);
    }

    return sub[i].parent;
}

void union_of_subsets(subset *sub, int x_root, int y_root) {
    if (sub[x_root].rank < sub[y_root].rank) {
        sub[x_root].parent = y_root;
    } else if (sub[x_root].rank > sub[y_root].rank) {
        sub[y_root].parent = x_root;
    } else {
        sub[y_root].parent = x_root;
        sub[x_root].rank++;
    }
}
