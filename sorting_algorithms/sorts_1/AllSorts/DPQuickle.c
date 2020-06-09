#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pcg_basic.h"

int comp;
int trans;

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

void qsDoublePivot(int lenght, int *elements) {
    if (lenght <= 5) { // tutaj eksperymentalny treshold
        InsertionSort(lenght, elements);
        return;
    }

    comp++;
    int p;
    int q;
    if (*(elements) > *(elements + lenght - 1)) { // 1 i ostatni jako pivoty p <= q
        q = *(elements);
        p = *(elements + lenght - 1);
        *(elements) = p;
        *(elements + lenght - 1) = q;
        trans++;
    } else {
        p = *(elements);
        q = *(elements + lenght - 1);
    }

    int less = 0;
    int more = 0;

    for (int i=1; i<lenght-1-more; i++) {
        if (more > less) {
            if (*(elements + i) > q) { // pierw porownujemy z q
                comp++; // to juz nam daje +1 w comp
                more++; // zwiekszamy more zeby zajac jedno miejsce
                for (int k=lenght-1-more; k > i; k--) { // tutaj dopoki z prawej bylo wieksze od q to zwiekszamy more az nie dojdziemy przed
                                                        // i pointer bo juz mamy wtedy more na i a wiemy ze *(elements + i) > *q
                    if (*(elements + k) > q) { // wieksze to zwiekszamy more
                        more++;
                        comp++;
                    } else if (*(elements + k) < p) { // moze byc dodatkowo mniejszy od p to wtedy nie ignorujemy go i nie sprawdzamy 2 razy tylko wrzucamy do less
                        less++;
                        int temp = *(elements + k);
                        *(elements + k) = *(elements + i);
                        *(elements + i) = *(elements + less);
                        *(elements + less) = temp;
                        trans+=2;
                        comp+=2;
                        break;
                    } else { // a jak nie to robimy swapa na i
                        int temp = *(elements + k);
                        *(elements + k) = *(elements + i);
                        *(elements + i) = temp;
                        trans++;
                        comp+=2;
                        break;
                    }
                }
            } else if (*(elements + i) < p) { // potem p
                trans++;
                comp+=2;
                less++;
                int temp = *(elements + i);
                *(elements + i) = *(elements + less); // tutaj wiemy ze wszystkie za less i przed *(elements + i) juz byly sprawdzone wiec swap
                *(elements + less) = temp;
            } else {
                comp+=2; // tutaj dodajemy comp bo nie bylismy w zadnym warunku ale porownalismy
            }
        } else {
            if (*(elements + i) < p) { // to samo co wyzej tylko w odwrotnej kolejnosci sprawdzania
                trans++;
                comp++;
                less++;
                int temp = *(elements + i);
                *(elements + i) = *(elements + less);
                *(elements + less) = temp;
            } else if (*(elements + i) > q) {
                comp+=2;
                more++;
                for (int k=lenght-1-more; k > i; k--) {
                    if (*(elements + k) > q) {
                        more++;
                        comp++;
                    } else if (*(elements + k) < p) { // moze byc dodatkowo mniejszy od p to wtedy nie ignorujemy go i nie sprawdzamy 2 razy tylko wrzucamy do less
                        less++;
                        int temp = *(elements + k);
                        *(elements + k) = *(elements + i);
                        *(elements + i) = *(elements + less);
                        *(elements + less) = temp;
                        trans+=2;
                        comp+=2;
                        break;
                    } else {
                        int temp = *(elements + k);
                        *(elements + k) = *(elements + i);
                        *(elements + i) = temp;
                        trans++;
                        comp+=2;
                        break;
                    }
                }
            } else {
                comp+=2;
            }
        }
    }

    // teraz swapik
    *(elements) = *(elements + less);
    *(elements + less) = p;

    *(elements + lenght - 1) = *(elements + lenght-1-more);
    *(elements + lenght-1-more) = q;

    trans += 2;

    qsDoublePivot(less, elements);
    qsDoublePivot(lenght - less-more-2, elements + less + 1);
    qsDoublePivot(more, elements + lenght-more);
}

void run_normal() {
    int lenght = 0;
    printf("Welcome to DualPivot QuickSort <=, enter lenght: ");
    scanf("%d", &lenght);
    int *elements = malloc(sizeof(int)*lenght);
    printf("Insert %d elements: ", lenght);
    for (int i=0; i<lenght; i++) {
        scanf("%d", elements+i);
    }

    clock_t t1;
    t1 = clock();
    qsDoublePivot(lenght, elements);
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
        qsDoublePivot(i*100, elements);
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