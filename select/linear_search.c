#include "linear_search.h"
#include "displayer.h"

void linear_search_min(int *arr, int size) {
    display_arr(stderr);
    int min = *arr;
    int min_pos = 0;
    for (int i=1; i<size; i++) {
        comp++;
        display_comparision(*(arr+i), min);
        if (*(arr+i) < min) {
            min = *(arr+i);
            min_pos = i;
        }
    }

    *(arr+min_pos) = *arr;
    *arr = min;
    trans++;
    display_transposition(*(arr+min_pos), min);
    display_rest();
}

void linear_search_max(int *arr, int size) {
    display_arr(stderr);
    int max = *arr;
    int max_pos = 0;
    for (int i=1; i<size; i++) {
        comp++;
        display_comparision(*(arr+i), max);
        if (*(arr+i) > max) {
            max = *(arr+i);
            max_pos = i;
        }
    }

    *(arr+max_pos) = *(arr+size-1);
    *(arr+size-1) = max;
    trans++;
    display_transposition(*(arr+max_pos), max);
    display_rest();
}