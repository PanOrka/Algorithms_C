#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pcg_basic.h"

int comp = 0;
int trans = 0;

void InsertionSort(int lenght, int *elements) {
    int key, j;
    for (int i = 1; i < lenght; i++) {
        key = *(elements + i);
        j = i - 1;
        while (j >= 0 && *(elements + j) > key) {
            *(elements + j + 1) = *(elements + j);
            j = j - 1;
            trans++;
            comp++;
        }
        if (j >= 0) { // jak petla nie weszla a spelnilismy warunek 1 to bylo porownanie
            comp++;
        }
        *(elements + j + 1) = key;
        trans++;
    }
}

void run_normal() {
    int lenght = 0;
    printf("Welcome to Insertion Sort <=, enter lenght: ");
    scanf("%d", &lenght);
    int *elements = malloc(sizeof(int)*lenght);
    printf("Insert %d elements: ", lenght);
    for (int i=0; i<lenght; i++) {
        scanf("%d", elements+i);
    }

    clock_t t1;
    t1 = clock();
    InsertionSort(lenght, elements);
    t1 = clock() - t1;
    fprintf(stderr, "Time clicks: %ld\nTime sec: %f\n", t1, ((double)t1/CLOCKS_PER_SEC));

    for (int i=1; i<lenght; i++) {
        if (*(elements+i) < *(elements+i-1)) {
            fprintf(stderr, "Array not sorted.\n");
            exit(1);
        }
    }

    for (int i=0; i<lenght; i++) {
        printf("%d, ", *(elements+i));
    }
    printf("\n");

    fprintf(stderr, "Comparisions = %d\n", comp);
    fprintf(stderr, "Transpositions = %d\n", trans);
}

void run_stats(FILE *file, pcg32_random_t *rng) {
    int *elements;
    
    for (int i=1; i<=100; i++) { // nasze wszystkie proby ze 100
        elements = malloc(sizeof(int)*i*100); // malloc dla 100*i elementow
        for (int k=0; k<i*100; k++) { // teraz losowanko i zapisywanie elementow pod pointer (zrobilem to pythonem bo ma fajne opcje random generator)
            *(elements+k) = (int)pcg32_boundedrand_r(rng, 20001) - 10000;
        }

        comp = 0;
        trans = 0;

        clock_t t1;
        t1 = clock();
        InsertionSort(i*100, elements);
        t1 = clock() - t1;
        fprintf(stderr, "Time clicks: %ld\nTime sec: %f\n", t1, ((double)t1/CLOCKS_PER_SEC));

        for (int k=1; k<i*100; k++) {
            if (*(elements+k) < *(elements+k-1)) {
                fprintf(stderr, "Array not sorted.\n");
                exit(1);
            }
        }

        fprintf(stderr, "Comparisions = %d\n", comp);
        fprintf(stderr, "Transpositions = %d\n", trans);
        printf("------------------------------------\n");

        // Saving to file SIZE_OF_ARRAY;time_clicks;time_sec;comparisions;transpositions
        // size of array
        fprintf(file, "%d", i*100);
        fprintf(file, "%s", ";"); // separator

        // time clicks
        fprintf(file, "%ld", t1);
        fprintf(file, "%s", ";"); // separator

        // time sec
        fprintf(file, "%f", ((double)t1/CLOCKS_PER_SEC));
        fprintf(file, "%s", ";"); // separator

        // comparisions
        fprintf(file, "%d", comp);
        fprintf(file, "%s", ";"); // separator

        // transpositions
        fprintf(file, "%d", trans);
        fprintf(file, "%s", "\n"); // new line

        free(elements);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        run_normal();
    } else { // argv[1] <- filename | argv[2] <- ilosc
        int amount_of_tests = atoi(argv[2]);
        FILE *file = fopen(argv[1], "a");
        fprintf(file, "SIZE_OF_ARRAY;time_clicks;time_sec;comparisions;transpositions\n");

        pcg32_random_t *rng = malloc(sizeof(pcg32_random_t));

        pcg32_srandom_r(rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&amount_of_tests); // seeding rng (non deterministic)

        for (int i=0; i<amount_of_tests; i++) {
            run_stats(file, rng);
        }
        fclose(file);
    }

    return 0;
}