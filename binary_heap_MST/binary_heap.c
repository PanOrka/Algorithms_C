#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "binary_heap.h"

#define INC_MAX_SIZE 20
#define parent(i) ((i-1)/2)
#define left(i) ((i+1)*2 - 1)
#define right(i) ((i+1)*2)


heap * create_heap(graph *g) {
    if (g->v_size > 0) {
        heap *h = malloc(sizeof(heap));
        h->tab = malloc(sizeof(node)*g->v_size);
        h->g = g;
        h->used_size = 0;
        h->max_size = g->v_size;

        return h;
    } else {
        return NULL;
    }
}

void insert_all(heap *h, int start) {
    h->tab->value = start;
    h->g->vertices[start].heap_place = 0;
    h->g->vertices[start].dist = 0;
    h->g->vertices[start].prev = -1;

    int counter = 1;
    for (int i=0; i<start; i++) {
        (h->tab + counter)->value = i;
        h->g->vertices[i].heap_place = counter;
        h->g->vertices[i].dist = __DBL_MAX__;
        h->g->vertices[i].prev = -1;
        counter++;
    }
    for (int i=start+1; i<h->max_size; i++) {
        (h->tab + counter)->value = i;
        h->g->vertices[i].heap_place = counter;
        h->g->vertices[i].dist = __DBL_MAX__;
        h->g->vertices[i].prev = -1;
        counter++;
    }

    h->used_size = h->max_size;
}

int is_empty(heap *h) {
    if (h->used_size == 0) {
        return 1;
    } else {
        return 0;
    }
}

void swap(node *ptr_1, node *ptr_2, vertice *v) {
    int temp_place = v[ptr_1->value].heap_place;
    v[ptr_1->value].heap_place = v[ptr_2->value].heap_place;
    v[ptr_2->value].heap_place = temp_place;

    node temp_node = *ptr_1;
    *ptr_1 = *ptr_2;
    *ptr_2 = temp_node;
}

node pop(heap *h) {
    if (is_empty(h)) {
        node ret_0 = {-1};
        fprintf(stderr, "VALUE ERROR: Returned empty node struct.\n");
        return ret_0;
    } else {
        node temp = *(h->tab);
        h->used_size--;
        vertice *v = h->g->vertices;
        if (h->used_size > 0) {
            v[h->tab->value].heap_place = -1;

            *(h->tab) = *(h->tab + h->used_size);
            v[h->tab->value].heap_place = 0;
            int i = 0;
            while (left(i) < h->used_size) {
                int k;
                if (right(i) < h->used_size) {
                    if (v[(h->tab + left(i))->value].dist <= v[(h->tab + right(i))->value].dist) {
                        k = left(i);
                    } else {
                        k = right(i);
                    }
                } else {
                    k = left(i);
                }

                if (v[(h->tab + i)->value].dist > v[(h->tab + k)->value].dist) {
                    swap((h->tab + i), (h->tab + k), v);
                    i = k;
                } else {
                    return temp;
                }
            }
        }
        
        return temp;
    }
}

void decrease_distance(heap *h, int i) {
    vertice *v = h->g->vertices;
    while (i>0 && v[(h->tab + i)->value].dist < v[(h->tab + parent(i))->value].dist) {
        swap((h->tab + i), (h->tab + parent(i)), v);
        i = parent(i);
    }
}
