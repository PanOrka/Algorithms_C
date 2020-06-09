#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *p;
    int value;
} element;

typedef struct {
    element *first;
    element *last;
} fifo;

fifo * createFifo() {
    fifo *f = malloc(sizeof(fifo));
    fifo f1 = {NULL, NULL};
    *f = f1;
    return f;
}

void put(fifo *f, int value) {
    if ((*f).first == NULL) { // patrzymy czy nasz pierwszy element jest NULL, wtedy calosc jest pusta
        element *el1 = malloc(sizeof(element));
        element el = {NULL, value};
        *el1 = el;
        (*f).first = el1;
        (*f).last = el1; // powielamy do ostatniego zeby byla ciaglosc przekazywania elementow do i z kolejki
    } else {
        element *el1 = malloc(sizeof(element)); // tutaj po prostu "wpychamy" element na koniec
        element el = {NULL, value};
        *el1 = el;
        (*((*f).last)).p = el1; // swap pointerow wskazujacych na nastepny "wpychany" element
        (*f).last = el1;  
    }
}

int get(fifo *f) {
    if ((*f).first == NULL && (*f).last == NULL) { // przypadek gdy kolejka jest pusta
        fprintf(stderr, "queue is empty\n");
        return -1;
    } else {
        element temp = (*((*f).first));
        free((*f).first);
        (*f).first = temp.p;
        if (temp.p == NULL) { // jesli wskazanie jest na NULL to znaczy ze first byl last
            (*f).last = NULL;
        }
        return temp.value;
    }
}

int main() {
    fifo *f = createFifo();

    printf("%d\n", get(f));
    put(f, 1);
    printf("%d\n", get(f));
    printf("%d\n", get(f));
    put(f, 1);
    put(f, 2);
    printf("%d\n", get(f));
    put(f, 3);
    put(f, 4);
    put(f, 5);
    printf("%d\n", get(f));
    printf("%d\n", get(f));
    printf("%d\n", get(f));
    printf("%d\n", get(f));
    printf("%d\n", get(f));
    put(f, 1);
    put(f, 2);
    put(f, 3);
    put(f, 4);
    put(f, 5);
    put(f, 6);
    printf("%d\n", get(f));
    printf("%d\n", get(f));
    put(f, 7);
    put(f, 8);
    put(f, 9);
    printf("%d\n", get(f));
    printf("%d\n", get(f));
    printf("%d\n", get(f));
    printf("%d\n", get(f));
    printf("%d\n", get(f));
    printf("%d\n", get(f));
    printf("%d\n", get(f));
    printf("%d\n", get(f));

    return 0;
}
