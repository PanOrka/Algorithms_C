#include "randomizer.h"

int *arr_to_display;
int size_of_display, k_place;

int trans, comp;

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

void linear_search_median(int *arr, int size, int kth) {

}

void random_select_search(int *arr, int size, int kth, pcg32_random_t *rng) {
    display_arr(stderr);
    if (size <= 1) {
        return;
    }

    int swap;
    int rand_select = (int)pcg32_boundedrand_r(rng, size);
    swap = *(arr+rand_select);
    display_pivot(swap);
    *(arr+rand_select) = *(arr+size-1);
    *(arr+size-1) = swap;
    trans++;
    display_transposition(swap, *(arr+rand_select));

    int div_p = *(arr+size-1); // biore div_p jako ostatni element tablicy, zawsze
    int index_left = 0;
    int index_right = size-2;

    while (index_left < index_right) { // to nasz warunek, robie na dwa "pointery"
        comp++;
        display_comparision(*(arr+index_left), div_p);
        if (*(arr+index_left) > div_p) {
            while (index_left < index_right) {
                comp++;
                display_comparision(*(arr+index_right), div_p);
                if (*(arr+index_right) <= div_p) {
                    swap = *(arr+index_right);
                    *(arr+index_right) = *(arr+index_left);
                    *(arr+index_left) = swap;
                    index_right--;
                    index_left++;
                    goto END; // jesli udal sie swap to robimy "break"
                } else {
                    index_right--;
                }
            }
            goto SWAP; // jesli nie bylo goto END to wtedy while() skonczyl sie na index_left == index_right i wiemy ze *(elements+index_right) <= div_p wiec mozemy swap
END:        trans++;
            display_transposition(*(arr+index_right+1), *(arr+index_left-1));
        } else {
            index_left++;
        }
    }

    comp++;
    display_comparision(*(arr+index_left), div_p);
    if (*(arr+index_left) > div_p) {
SWAP:   *(arr+size-1) = *(arr+index_left);
        *(arr+index_left) = div_p;
        index_left--;
        trans++;
        display_transposition(*(arr+size-1), div_p);
    } else { // w tym wypadku skonczylismy na ostatniej mniejszej lub rownej od div_p wiec swapujemy kolejna z div_p
        *(arr+size-1) = *(arr+index_left+1); // czasami swapniemy div_p z samym soba, probowalem jakos to zrobic ale jednak zostalo :(
        *(arr+index_left+1) = div_p;
        trans++;
        display_transposition(*(arr+size-1), div_p);
    }

    display_rest();

    if (index_left+2 == kth) {
        return;
    } else if (kth < index_left+2) {
        random_select_search(arr, index_left+1, kth, rng);
    } else {
        random_select_search(arr+index_left+2, size-index_left-2, kth-(index_left+2), rng);
    }
}

void random_select(int *arr, int size, int kth) {
    arr_to_display = arr;
    size_of_display = size;
    k_place = kth;

    if (kth == 1) {
        linear_search_min(arr, size);
    } else if (kth == size) {
        linear_search_max(arr, size);
    } else if (kth == (size+1)/2) {
        linear_search_median(arr, size, kth);
    } else {
        pcg32_random_t rng;
        pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&size);
        random_select_search(arr, size, kth, &rng);
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
            random_select(arr, size, kth);
        } else if (strcmp(argv[1], "-p") == 0) {
            int size, kth;
            scanf("%d", &size);
            scanf("%d", &kth);
            int *arr = random_permutation(size);
            random_select(arr, size, kth);
        } else {
            fprintf(stderr, "Wrong argument\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "Wrong amount of arguments\n");
        exit(1);
    }
}