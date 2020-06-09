#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "graph.h"

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

void Djikstra(graph *g, int start) {
    heap *h = create_heap(g);
    insert_all(h, start);
    vertice *v = g->vertices;

    while (is_empty(h) == 0) {
        node u = pop(h);
        list *n = v[u.value].n;
        while (n != NULL) {
            if (v[n->v].dist > v[u.value].dist + n->weight) {
                v[n->v].dist = v[u.value].dist + n->weight;
                v[n->v].prev = u.value;
                decrease_distance(h, v[n->v].heap_place);
            }
            n = n->next;
        }
    }
    for (int i=0; i<g->v_size; i++) {
        if ((v + i)->prev >= 0) {
            printf("%d %lf\n", i, (v + i)->dist);
        } else {
            printf("%d UNREACHABLE\n", i);
        }
    }

    for (int i=0; i<g->v_size; i++) {
        int arr[g->v_size];
        double weight[g->v_size];
        int ctr = 0;
        int node = i;
        while (node != start) {
            arr[ctr] = node;
            weight[ctr] = (v + node)->dist;
            if (ctr != 0) {
                weight[ctr-1] -= weight[ctr];
            }
            ctr++;
            node = (v + node)->prev;
        }
        arr[ctr] = node;
        weight[ctr-1] -= (v+node)->dist;
        for (int k=ctr; k>0; k--) {
            fprintf(stderr, "%d -( %lf )-> ", arr[k], weight[k-1]);
        }
        fprintf(stderr, "%d\n", arr[0]);
    }
}

int main() {
    clock_t time_start = clock();
    int e_size, v_size;
    scanf("%d", &v_size);
    scanf("%d", &e_size);
    graph *g = create_graph(v_size, e_size);
    vertice *v = g->vertices;
    for (int i=0; i<e_size; i++) {
        int from, to;
        double weight;
        scanf("%d", &from);
        scanf("%d", &to);
        scanf("%lf", &weight);
        list *new = malloc(sizeof(list));
        new->next = v[from].n;
        new->v = to;
        new->weight = weight;
        v[from].n = new;
    }
    int start;
    scanf("%d", &start);
    Djikstra(g, start);
    fprintf(stderr, "%lf", ((double)(clock() - time_start)/CLOCKS_PER_SEC)*1000);
}
