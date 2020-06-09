#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "rw_lw/graph.h"
#include "MST_euler_cycle/graph.h"


/*
// Free allocated memory for graph_rw
*/
graph_2 * free_graph_rw(graph_rw *g) {
    int v_size = g->v_size;
    int e_size = (v_size*(v_size - 1))/2;
    graph_2 *g_2 = create_graph_2(v_size, e_size);
    edge *e = g_2->edges;

    int counter = 0;
    for (int i=0; i<g->v_size - 1; i++) {
        for (int k=i+1; k<v_size; k++) {
            e[counter].u = i;
            e[counter].v = k;
            e[counter].weight = ((g->vertices + i)->n + k - (i + 1))->weight;
            counter++;
        }
        free((g->vertices + i)->n);
    }
    free(g->vertices);
    free(g);

    return g_2;
}

int path_ctr, step_ctr;
/*
// Traverse mst from node actual
*/
void traverse_mst(int actual, mst *tree, int *traversed) {
    e_lst *n = (tree->vertices + actual)->n;
    (tree->vertices + actual)->was_explored = true;
    *(traversed + path_ctr) = actual;
    path_ctr++;

    while (n != NULL) {
        if (!(tree->vertices + n->v)->was_explored) {
            step_ctr++;
            traverse_mst(n->v, tree, traversed);
            step_ctr++; // back-tracking
        }
        n = n->next;
    }
}

/*
// Free allocated memory for kruskal's graph
*/
graph * free_graph_kruskal(graph_2 *g) {
    graph *g_2 = create_graph(g->v_size, g->e_size);
    vertice *v = g_2->vertices;

    for (int i=0; i<g->e_size; i++) {
        int from = g->edges[i].u;
        int to = g->edges[i].v;
        double weight = g->edges[i].weight;

        // index shift
        if (to < from) {
            ((v + from)->n + to)->weight = weight;
            ((v + from)->n + to)->v = to;

            ((v + to)->n + from - 1)->weight = weight;
            ((v + to)->n + from - 1)->v = from;
        } else {
            ((v + from)->n + to - 1)->weight = weight;
            ((v + from)->n + to - 1)->v = to;

            ((v + to)->n + from)->weight = weight;
            ((v + to)->n + from)->v = from;
        }
    }
    free(g->edges);
    free(g);

    return g_2;
}

typedef struct {
    double w_prim, w_kruskal;
} mst_path_cost;

/*
// Printing cut traversal
*/
mst_path_cost print_traversal(graph *g, int *traversed_kruskal, int *traversed_prim) {
    vertice *v = g->vertices;

    mst_path_cost cost = {0.0, 0.0};

    fprintf(stderr, "MST Prim Strategy:\n");
    for (int i=0; i<g->v_size-1; i++) {
        int next;
        if (traversed_prim[i] < traversed_prim[i+1]) {
            next = traversed_prim[i+1] - 1;
        } else {
            next = traversed_prim[i+1];
        }
        double w = ((v + traversed_prim[i])->n + next)->weight;
        cost.w_prim += w;
        fprintf(stderr, "%d -( %lf )-> ", traversed_prim[i], w);
    }
    fprintf(stderr, "%d\n", traversed_prim[g->v_size - 1]);

    fprintf(stderr, "MST Kruskal Strategy:\n");
    for (int i=0; i<g->v_size-1; i++) {
        int next;
        if (traversed_kruskal[i] < traversed_kruskal[i+1]) {
            next = traversed_kruskal[i+1] - 1;
        } else {
            next = traversed_kruskal[i+1];
        }
        double w = ((v + traversed_kruskal[i])->n + next)->weight;
        cost.w_kruskal += w;
        fprintf(stderr, "%d -( %lf )-> ", traversed_kruskal[i], w);
    }
    fprintf(stderr, "%d\n", traversed_kruskal[g->v_size - 1]);

    return cost;
}

/*
// Traversing graph with Random-Walk and Lowest-Weight Strategy
*/
graph_rw * rw_graph(int v_size) {
    struct timespec t1, t2;
    long long elapsed;

    /*
    // Random walk
    */

    graph_rw *g = create_graph_rw(v_size); // malloc
    graph_rw_take_stdin(g);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);

    traverse_rw(g);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
    if (t2.tv_sec - t1.tv_sec > 0) {
        elapsed = (long long)(t2.tv_sec - t1.tv_sec)*1000000000;
        elapsed += (long long)t2.tv_nsec - t1.tv_nsec;
    } else {
        elapsed = (long long)t2.tv_nsec - t1.tv_nsec;
    }
    printf("%lf (ms)\n", (double)elapsed/1000000);

    clear_flag_rw(g);

    /*
    // Lowest weight
    */

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);

    traverse_lw(g);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
    if (t2.tv_sec - t1.tv_sec > 0) {
        elapsed = (long long)(t2.tv_sec - t1.tv_sec)*1000000000;
        elapsed += (long long)t2.tv_nsec - t1.tv_nsec;
    } else {
        elapsed = (long long)t2.tv_nsec - t1.tv_nsec;
    }
    printf("%lf (ms)\n", (double)elapsed/1000000);

    return g;
}

/*
// Traversing graph with MST strategy
*/
void mst_graphs(graph_rw *g) {
    struct timespec t1, t2;
    long long elapsed_1, elapsed_2;

    /*
    // Kruskal Strategy
    */

    graph_2 *g_2 = free_graph_rw(g);
    int *traversed = malloc(sizeof(int)*(g_2->v_size));
    for (int i=0; i<g_2->v_size; i++) {
        traversed[i] = -1;
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);

    mst *tree = kruskal_mst(g_2);
    traverse_mst(0, tree, traversed);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
    if (t2.tv_sec - t1.tv_sec > 0) {
        elapsed_1 = (long long)(t2.tv_sec - t1.tv_sec)*1000000000;
        elapsed_1 += (long long)t2.tv_nsec - t1.tv_nsec;
    } else {
        elapsed_1 = (long long)t2.tv_nsec - t1.tv_nsec;
    }

    /*
    // Prim Strategy
    */

    graph *g_3 = free_graph_kruskal(g_2);
    int *traversed_2 = malloc(sizeof(int)*(g_3->v_size));
    for (int i=0; i<g_3->v_size; i++) {
        traversed_2[i] = -1;
    }
    path_ctr = 0;
    int step_ctr_kruskal = step_ctr;
    step_ctr = 0;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);

    mst *tree_2 = prim_mst(g_3, 0);
    traverse_mst(0, tree_2, traversed_2);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
    if (t2.tv_sec - t1.tv_sec > 0) {
        elapsed_2 = (long long)(t2.tv_sec - t1.tv_sec)*1000000000;
        elapsed_2 += (long long)t2.tv_nsec - t1.tv_nsec;
    } else {
        elapsed_2 = (long long)t2.tv_nsec - t1.tv_nsec;
    }

    /*
    // Printing mst traversals
    */
    mst_path_cost cost = print_traversal(g_3, traversed, traversed_2);
    /*
    // memory for heap, heap nodes as edge values in edges array, heap place in edges, subset {int, int}
    */
    printf("MST Kruskal: %d, %lf, %ld (bytes), %lf (ms)\n", step_ctr_kruskal, cost.w_kruskal,
        sizeof(heap_2) + sizeof(node_2)*(g_3->e_size) + sizeof(int)*(g_3->e_size) + sizeof(int)*(g_3->v_size)*2, (double)elapsed_1/1000000);
    /*
    // memory for heap, heap nodes as vertice values in vertice array, heap place in vertices, explored array, distance of previous
    */
    printf("MST Prim: %d, %lf, %ld (bytes), %lf (ms)\n", step_ctr, cost.w_prim,
        sizeof(heap) + sizeof(node)*(g_3->v_size) + sizeof(int)*(g_3->v_size)*2 + sizeof(double)*(g_3->v_size), (double)elapsed_2/1000000);
}

int main() {
    int v_size;
    scanf("%d", &v_size);
    graph_rw *g = rw_graph(v_size);

    mst_graphs(g);
}
