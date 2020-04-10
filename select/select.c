#include "randomizer.h"
#include "linear_search.h"
#include "select_algorithm.h"
#include "displayer.h"

void select_start(int *arr, int size, int kth) {
    arr_to_display = arr;
    size_of_display = size;
    k_place = kth;

    if (kth == 1) {
        linear_search_min(arr, size);
    } else if (kth == size) {
        linear_search_max(arr, size);
    } else {
        select_search(arr, size, kth);
    }

    display_arr(stdout);
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        if (strcmp(argv[1], "-r") == 0) {
            int size, kth;
            scanf("%d", &size);
            scanf("%d", &kth);
            int *arr = random_data(size);
            select_start(arr, size, kth);
        } else if (strcmp(argv[1], "-p") == 0) {
            int size, kth;
            scanf("%d", &size);
            scanf("%d", &kth);
            int *arr = random_permutation(size);
            select_start(arr, size, kth);
        } else {
            fprintf(stderr, "Wrong argument\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "Wrong amount of arguments\n");
        exit(1);
    }
}