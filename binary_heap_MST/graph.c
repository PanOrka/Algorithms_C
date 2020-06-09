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
            (g->vertices + i)->n = NULL;
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

void prim_mst(graph *g, int start) {
    heap *h = create_heap(g);
    insert_all(h, start);
    vertice *v = g->vertices;

    int v_explored[g->v_size];
    for (int i=0; i<g->v_size; i++) {
        v_explored[i] = 0;
    }
    mst *tree = malloc(sizeof(mst)*(g->v_size-1));
    int tree_size = 0;

    while (is_empty(h) == 0) {
        node u = pop(h);
        if (v[u.value].prev != -1) {
            tree[tree_size].u = u.value;
            tree[tree_size].v = v[u.value].prev;
            tree[tree_size].weight = v[u.value].dist;

            tree_size++;
        }
        v_explored[u.value] = 1;
        list *n = v[u.value].n;
        while (n != NULL) {
            if (v[n->v].dist > n->weight && v_explored[n->v] == 0) { // Ustalamy dystans tylko tam
                v[n->v].dist = n->weight;                            // gdzie nie bylismy w drzewie
                v[n->v].prev = u.value;
                decrease_distance(h, v[n->v].heap_place);
            }
            n = n->next;
        }
    }

    double sum = 0;
    for (int i=0; i<tree_size; i++) {
        printf("(%d, %d, %lf)\n", tree[i].u, tree[i].v, tree[i].weight);
        sum += tree[i].weight;
    }
    printf("SUM of edges: %lf", sum);
}

void take_stdin_prim(vertice *v, int v_size, int e_size) {
    int repeat[v_size][v_size]; // VLA just for repeat
    for (int i=0; i<v_size; i++) {
        for (int k=0; k<v_size; k++) {
            repeat[i][k] = 0;
        }
    }
    for (int i=0; i<e_size; i++) {
        int from, to;
        double weight;
        scanf("%d", &from);
        scanf("%d", &to);
        scanf("%lf", &weight);
        if (repeat[from][to] == 0) {
            list *new_1 = malloc(sizeof(list));
            new_1->next = v[from].n;
            new_1->v = to;
            new_1->weight = weight;
            v[from].n = new_1;

            list *new_2 = malloc(sizeof(list));
            new_2->next = v[to].n;
            new_2->v = from;
            new_2->weight = weight;
            v[to].n = new_2;

            repeat[from][to] = 1;
            repeat[to][from] = 1;
        }
    }
}

void kruskal_mst(graph_2 *g) {
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

    mst *tree = malloc(sizeof(mst)*(g->v_size-1));
    int tree_size = 0;

    /*
    // |V|-1 vertices for whole MST
    */
    while (is_empty_2(h) == 0 && tree_size < g->v_size-1) {
        node_2 u = pop_2(h);

        int u_root = find(sub, e[u.value].u);
        int v_root = find(sub, e[u.value].v);
        if (u_root != v_root) {
            tree[tree_size].u = e[u.value].u;
            tree[tree_size].v = e[u.value].v;
            tree[tree_size].weight = e[u.value].weight;

            tree_size++;

            /*
            // Not in same set, so Union of sets
            */
            union_of_subsets(sub, u_root, v_root);
        }
    }

    double sum = 0;
    for (int i=0; i<tree_size; i++) {
        printf("(%d, %d, %lf)\n", tree[i].u, tree[i].v, tree[i].weight);
        sum += tree[i].weight;
    }
    printf("SUM of edges: %lf", sum);
}

void take_stdin_kruskal(graph_2 *g, int v_size, int e_size) {
    edge *e = g->edges;
    int repeat[v_size][v_size]; // VLA just for repeat
    for (int i=0; i<v_size; i++) {
        for (int k=0; k<v_size; k++) {
            repeat[i][k] = 0;
        }
    }
    int counter = 0;
    for (int i=0; i<e_size; i++) {
        int from, to;
        double weight;
        scanf("%d", &from);
        scanf("%d", &to);
        scanf("%lf", &weight);
        if (repeat[from][to] == 0) {
            e[counter].u = from;
            e[counter].v = to;
            e[counter].weight = weight;

            repeat[from][to] = 1;
            repeat[to][from] = 1;
            counter++;
        }
    }
    if (counter < g->e_size) {
        g->e_size = counter;
        edge *temp_edge = malloc(sizeof(edge)*g->e_size);
        for (int i=0; i<g->e_size; i++) {
            (temp_edge + i)->u = (e + i)->u;
            (temp_edge + i)->v = (e + i)->v;
            (temp_edge + i)->weight = (e + i)->weight;
        }
        free(e);
        g->edges = temp_edge;
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int e_size, v_size;
        scanf("%d", &v_size);
        scanf("%d", &e_size);
        if (strcmp(argv[1], "-p") == 0) {
            graph *g = create_graph(v_size, e_size);
            vertice *v = g->vertices;

            take_stdin_prim(v, v_size, e_size);

            int start = 0;
            prim_mst(g, start);
        } else if (strcmp(argv[1], "-k") == 0) {
            graph_2 *g = create_graph_2(v_size, e_size);

            take_stdin_kruskal(g, v_size, e_size);

            kruskal_mst(g);
        }
    } else {
        fprintf(stderr, "Not enough arguments.\n");
    }
}
