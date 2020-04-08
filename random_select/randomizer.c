#include "randomizer.h"

int * random_permutation(int size) {
    pcg32_random_t rng;
    pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&size);

    int *perm = malloc(sizeof(int)*size);
    for (int i=0; i<size; i++) {
        *(perm+i) = i+1;
    }

    int r1, r2, temp;
    for (int i=0; i<size/2; i++) {
        r1 = (int)pcg32_boundedrand_r(&rng, size);
        r2 = (int)pcg32_boundedrand_r(&rng, size);
        temp = *(perm+r1);
        *(perm+r1) = *(perm+r2);
        *(perm+r2) = temp;
    }

    fprintf(stderr, "Random permutation: ");
    for (int i=0; i<size; i++) {
        fprintf(stderr, "%d, ", *(perm+i));
    }
    fprintf(stderr, "\n");

    return perm;
}

int * random_data(int size) {
    pcg32_random_t rng;
    pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&size);

    int *arr = malloc(sizeof(int)*size);
    for (int i=0; i<size; i++) {
        *(arr+i) = (int)pcg32_boundedrand_r(&rng, INT32_MAX) - (int)pcg32_boundedrand_r(&rng, INT32_MAX);
    }

    fprintf(stderr, "Random data: ");
    for (int i=0; i<size; i++) {
        fprintf(stderr, "%d, ", *(arr+i));
    }
    fprintf(stderr, "\n");

    return arr;
}