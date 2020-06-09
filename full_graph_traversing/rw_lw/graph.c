#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include "graph.h"
#include "pcg_basic.h"


graph_rw * create_graph_rw(int v_size) {
    graph_rw *g = malloc(sizeof(graph_rw));
    g->v_size = v_size;
    g->vertices = malloc(sizeof(vertice_rw)*v_size);

    // Optimalization to keep |E| not 2*|E|
    for (int i=0; i<v_size; i++) {
        (g->vertices + i)->was_explored = false;
        if (v_size - 1 - i > 0) {
            (g->vertices + i)->n = malloc(sizeof(edge_rw)*(v_size - (i + 1)));
        } else {
            (g->vertices + i)->n = NULL;
        }
    }

    return g;
}


// later change stdin to run.c
void graph_rw_take_stdin(graph_rw *g) {
    int e_size = ((g->v_size)*(g->v_size - 1))/2;
    for (int i=0; i<e_size; i++) {
        int from, to;
        double weight;
        scanf("%d %d %lf", &from, &to, &weight);
        if (to < from) {
            // indexing after to
            ((g->vertices + to)->n + from - (to + 1))->weight = weight;
        } else {
            // indexing after from
            ((g->vertices + from)->n + to - (from + 1))->weight = weight;
        }
    }
}


void traverse_rw(graph_rw *g) {
    pcg32_random_t rng;
    pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&(g->v_size));
    int visited_counter = 1;

    fprintf(stderr, "Random Walk Strategy:\n");
    vertice_rw *v = g->vertices;
    int v_start = (int)pcg32_boundedrand_r(&rng, g->v_size);
    (v + v_start)->was_explored = true;

    double sum_weight = 0;
    while (visited_counter < g->v_size) {
        /*
        // size of neighbour is v_size - 1,
        // getting random index to traverse edge
        */
        int i = (int)pcg32_boundedrand_r(&rng, g->v_size);
        while ((v + i)->was_explored) {
            i = (int)pcg32_boundedrand_r(&rng, g->v_size);
        }
        double weight;
        if (i < v_start) {
            edge_rw *n = (v + i)->n;
            weight = (n + v_start - (i + 1))->weight;
        } else {
            edge_rw *n = (v + v_start)->n;
            weight = (n + i - (v_start + 1))->weight;
        }
        (v + i)->was_explored = true;
        sum_weight += weight;

        fprintf(stderr, "%d -( %lf )-> ", v_start, weight);

        v_start = i;
        visited_counter++;
    }
    fprintf(stderr, "%d\n", v_start);

    printf("Random Walk: %d, %lf, %ld (bytes), ", g->v_size-1, sum_weight, g->v_size*sizeof(bool));
}


void clear_flag_rw(graph_rw *g) {
    for (int i=0; i<g->v_size; i++) {
        (g->vertices + i)->was_explored = false;
    }
}


void traverse_lw(graph_rw *g) {
    pcg32_random_t rng;
    pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)g);
    int visited_counter = 1;

    fprintf(stderr, "Lowest Weight Walk Strategy:\n");
    vertice_rw *v = g->vertices;
    int v_start = (int)pcg32_boundedrand_r(&rng, g->v_size);
    (v + v_start)->was_explored = true;

    double sum_weight = 0;
    while (visited_counter < g->v_size) {
        double weight = __DBL_MAX__;
        int best_node = -1;
        for (int i=0; i<g->v_size; i++) {
            if (!(v + i)->was_explored) {
                if (i < v_start) {
                    edge_rw *n = (v + i)->n;
                    double temp = (n + v_start - (i + 1))->weight;

                    if (weight > temp) {
                        weight = temp;
                        best_node = i;
                    }
                } else {
                    edge_rw *n = (v + v_start)->n;
                    double temp = (n + i - (v_start + 1))->weight;

                    if (weight > temp) {
                        weight = temp;
                        best_node = i;
                    }
                }
            }
        }

        (v + best_node)->was_explored = true;
        sum_weight += weight;

        fprintf(stderr, "%d -( %lf )-> ", v_start, weight);

        v_start = best_node;
        visited_counter++;
    }
    fprintf(stderr, "%d\n", v_start);

    printf("Lowest Edge Weight: %d, %lf, %ld (bytes), ", g->v_size-1, sum_weight, g->v_size*sizeof(bool));
}
