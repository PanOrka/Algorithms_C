#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "disjoint_set.h"

graph * create_graph(int v_size, int e_size) {
    if (v_size > 0 && e_size > 0) {
        graph *g = malloc(sizeof(graph));
        g->v_size = v_size;
        g->e_size = e_size;
        g->vertices = malloc(sizeof(vertice)*v_size);
        for (int i=0; i<g->v_size; i++) {
            (g->vertices + i)->n = malloc(sizeof(neighbours)*(v_size - 1));
        }

        return g;
    } else {
        return NULL;
    }
}

graph_2 * create_graph_2(int v_size, int e_size) {
    if (v_size > 0 && e_size > 0) {
        graph_2 *g = malloc(sizeof(graph_2));
        g->v_size = v_size;
        g->e_size = e_size;
        g->edges = malloc(sizeof(edge)*e_size);

        return g;
    } else {
        return NULL;
    }
}

mst * prim_mst(graph *g, int start) {
    heap *h = create_heap(g);
    insert_all(h, start);
    vertice *v = g->vertices;

    int v_explored[g->v_size];
    for (int i=0; i<g->v_size; i++) {
        v_explored[i] = 0;
    }
    mst *tree = malloc(sizeof(mst));
    tree->vertices = malloc(sizeof(vertice_mst)*g->v_size);
    for (int i =0; i<g->v_size; i++) {
        (tree->vertices + i)->n = NULL;
        (tree->vertices + i)->was_explored = false;
    }

    while (is_empty(h) == 0) {
        node u = pop(h);
        if (v[u.value].prev != -1) {
            e_lst *new_e_1 = malloc(sizeof(e_lst));
            new_e_1->next = (tree->vertices + u.value)->n;
            new_e_1->weight = v[u.value].dist;
            new_e_1->v = v[u.value].prev;
            (tree->vertices + u.value)->n = new_e_1;

            e_lst *new_e_2 = malloc(sizeof(e_lst));
            new_e_2->next = (tree->vertices + v[u.value].prev)->n;
            new_e_2->weight = v[u.value].dist;
            new_e_2->v = u.value;
            (tree->vertices + v[u.value].prev)->n = new_e_2;
        }
        v_explored[u.value] = 1;

        for (int i=0; i<g->v_size-1; i++) {
            neighbours *n = v[u.value].n + i;
            if (v[n->v].dist > n->weight && v_explored[n->v] == 0) { // Ustalamy dystans tylko tam
                v[n->v].dist = n->weight;                            // gdzie nie bylismy w drzewie
                v[n->v].prev = u.value;
                decrease_distance(h, v[n->v].heap_place);
            }
        }
    }

    free(h->tab);
    free(h);

    return tree;
}

mst * kruskal_mst(graph_2 *g) {
    heap_2 *h = create_heap_2(g);
    insert_all_2(h);
    edge *e = g->edges;

    /*
    // Using disjoint_sets to fast check cycles
    */
    subset sub[g->v_size];
    for (int i=0; i<g->v_size; i++) {
        sub[i].parent = i;
        sub[i].rank = 0;
    }

    mst *tree = malloc(sizeof(mst));
    tree->vertices = malloc(sizeof(vertice_mst)*g->v_size);
    for (int i =0; i<g->v_size; i++) {
        (tree->vertices + i)->n = NULL;
        (tree->vertices + i)->was_explored = false;
    }
    int tree_size = 0;

    /*
    // |V|-1 vertices for whole MST
    */
    while (is_empty_2(h) == 0 && tree_size < g->v_size-1) {
        node_2 u = pop_2(h);

        int u_root = find(sub, e[u.value].u);
        int v_root = find(sub, e[u.value].v);
        if (u_root != v_root) {
            e_lst *new_e_1 = malloc(sizeof(e_lst));
            new_e_1->next = (tree->vertices + e[u.value].u)->n;
            new_e_1->weight = e[u.value].weight;
            new_e_1->v = e[u.value].v;
            (tree->vertices + e[u.value].u)->n = new_e_1;

            e_lst *new_e_2 = malloc(sizeof(e_lst));
            new_e_2->next = (tree->vertices + e[u.value].v)->n;
            new_e_2->weight = e[u.value].weight;
            new_e_2->v = e[u.value].u;
            (tree->vertices + e[u.value].v)->n = new_e_2;

            tree_size++;

            /*
            // Not in same set, so Union of sets
            */
            union_of_subsets(sub, u_root, v_root);
        }
    }

    free(h->tab);
    free(h);

    return tree;
}
