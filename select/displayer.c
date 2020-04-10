#include "displayer.h"

void display_arr(FILE *out) {
    for (int i=0; i<k_place-1; i++) {
        fprintf(out, "%d ", *(arr_to_display+i));
    }

    fprintf(out, "[%d] ", *(arr_to_display+k_place-1));

    for (int i=k_place; i<size_of_display; i++) {
        fprintf(out, "%d ", *(arr_to_display+i));
    }
    fprintf(out, "\n");
}

void display_rest() {
    fprintf(stderr, "==\nComparisions: %d, Transpositions: %d, k: %d\n==\n", comp, trans, k_place);
}

void display_pivot(int value) {
    fprintf(stderr, "==\nPivot value: %d\n==\n", value);
}

void display_comparision(int f_place, int s_place) {
    fprintf(stderr, "==\nCompared values: %d, %d\n==\n",f_place, s_place);
}

void display_transposition(int f_place, int s_place) {
    fprintf(stderr, "==\nTransposed values: %d, %d\n==\n", f_place, s_place);
    fprintf(stderr, "==\nArray after Transposition:\n==\n");
    display_arr(stderr);
}