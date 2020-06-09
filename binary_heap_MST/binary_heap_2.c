#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "binary_heap_2.h"

#define INC_MAX_SIZE 20
#define parent(i) ((i-1)/2)
#define left(i) ((i+1)*2 - 1)
#define right(i) ((i+1)*2)


heap_2 * create_heap_2(graph_2 *g) {
    if (g->e_size > 0) {
        heap_2 *h = malloc(sizeof(heap_2));
        h->tab = malloc(sizeof(node_2)*g->e_size);
        h->g = g;
        h->used_size = 0;
        h->max_size = g->e_size;

        return h;
    } else {
        return NULL;
    }
}

void insert(heap_2 *h, int value) {
    edge *e = h->g->edges;
    if (h->used_size < h->max_size) {
        int i = h->used_size;
        while (i>0 && e[(h->tab + parent(i))->value].weight > e[value].weight) {
            *(h->tab + i) = *(h->tab + parent(i));
            i = parent(i);
        }
        (h->tab + i)->value = value;

        h->used_size += 1;
    }
}

void insert_all_2(heap_2 *h) {
    for (int i=0; i<h->max_size; i++) {
        insert(h, i);
    }
}

int is_empty_2(heap_2 *h) {
    if (h->used_size == 0) {
        return 1;
    } else {
        return 0;
    }
}

void swap_2(node_2 *ptr_1, node_2 *ptr_2, edge *e) {
    int temp_place = e[ptr_1->value].heap_place;
    e[ptr_1->value].heap_place = e[ptr_2->value].heap_place;
    e[ptr_2->value].heap_place = temp_place;

    node_2 temp_node = *ptr_1;
    *ptr_1 = *ptr_2;
    *ptr_2 = temp_node;
}

node_2 pop_2(heap_2 *h) {
    if (is_empty_2(h)) {
        node_2 ret_0 = {-1};
        fprintf(stderr, "VALUE ERROR: Returned empty node struct.\n");
        return ret_0;
    } else {
        node_2 temp = *(h->tab);
        h->used_size--;
        edge *e = h->g->edges;
        if (h->used_size > 0) {
            e[h->tab->value].heap_place = -1;

            *(h->tab) = *(h->tab + h->used_size);
            e[h->tab->value].heap_place = 0;
            int i = 0;
            while (left(i) < h->used_size) {
                int k;
                if (right(i) < h->used_size) {
                    if (e[(h->tab + left(i))->value].weight <= e[(h->tab + right(i))->value].weight) {
                        k = left(i);
                    } else {
                        k = right(i);
                    }
                } else {
                    k = left(i);
                }

                if (e[(h->tab + i)->value].weight > e[(h->tab + k)->value].weight) {
                    swap_2((h->tab + i), (h->tab + k), e);
                    i = k;
                } else {
                    return temp;
                }
            }
        }
        
        return temp;
    }
}

void decrease_distance_2(heap_2 *h, int i) {
    edge *e = h->g->edges;
    while (i>0 && e[(h->tab + i)->value].weight < e[(h->tab + parent(i))->value].weight) {
        swap_2((h->tab + i), (h->tab + parent(i)), e);
        i = parent(i);
    }
}
