#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    void *p; // void tylko dlatego ze przy typedef struct list -Wall i -pedantic wyrzucaja warny
    int value;
} list;

void addElement(list **p, int value) { // idziemy do konca listy i podajemy pointer na miejsce pamieci gdzie mamy nowy struct z wartoscia value
    list *new_element = malloc(sizeof(list));
    list el1 = {NULL, value};
    *new_element = el1;

    if (*p == NULL) {
        *p = new_element;
    } else {
        list *p1 = *p;
        while ((*p1).p != NULL) {
            p1 = (*p1).p;
        }
        (*p1).p = new_element;
    }
}

void deleteElement(list **p, int n) {
    list *swap; // ustalamy swap, czyli element n ktory chcemy usunac, bo potrzebujemy elementu n+1

    if ((*p) == NULL) {
        fprintf(stderr, "List has no elements\n");
        return;
    }

    if (n == 0) {
        swap = (**p).p;
        free(*p);
        *p = swap;
    } else {
        list *p2 = *p;
        for (int i=1; i<=n; i++) {
            swap = p2;
            if ((*p2).p != NULL) { // tak otrzymamy pod p2 element n oraz pod swap element n-1
                p2 = (*p2).p;
            } else {
                fprintf(stderr, "Out of list bounds, list size = %d\n", i);
                return;
            }
        }

        (*swap).p = (*p2).p;
        free(p2);
    }
}

void showList(list *p) {
    printf("== LIST ==\n");
    while (p != NULL) {
        printf("%d\n", (*p).value);
        p = (*p).p;
    }
    printf("==========\n");
}

list * getElement(list *p, int n) {
    if (p == NULL) {
        fprintf(stderr, "Error: List is empty\n");
        exit(1);
    }

    for (int i=0; i<n; i++) {
        if ((*p).p != NULL) {
            p = (*p).p;
        } else {
            fprintf(stderr, "Out of list bounds, last element of list is returned, list size = %d\n", i);
            break;
        }
    }

    return p;
}

void merge(list *list1, list **list2) { // Dolacza poczatek listy2 do konca listy1 i usuwamy referencje do poczatku listy2 zeby nie bylo mozna zmieniac ich wzajemnie
    while ((*list1).p != NULL) {
        list1 = (*list1).p;
    }

    (*list1).p = *list2; // ustawiamy pointer ostatniego elementu na element nr 0 z listy2

    *list2 = NULL; // bez tego mamy nadal wskazanie na jakies miejsce w pamieci, na dole test czy to dziala
}

void deleteList(list **p) {
    list *helper;
    while (*p != NULL) {
        helper = *p;
        *p = (**p).p;
        free(helper);
    }
}

list * createList() {
    return NULL;
}

int main() {

    list *lista = createList();
    
    int exactElement = 500; // 500 = wartosc oczekiwana rozkladu jednostajnego
    clock_t t1;
    clock_t t2;

    for (int i=0; i<1000; i++) {
        addElement(&lista, i);
    }

    t1 = clock();
    for (int i=0; i<1000; i++) {
        getElement(lista, exactElement);
    }
    t1 = clock() - t1;
    printf("%d element time:\nclicks: %ld\nseconds: %f\n", exactElement, t1, ((double)t1/CLOCKS_PER_SEC));

    t2 = clock();
    for (int i=0; i<1000; i++) {
        getElement(lista, i);
    }
    t2 = clock() - t2;
    printf("Random element time\nclicks: %ld\nseconds: %f\n", t2, ((double)t2/CLOCKS_PER_SEC));

    /*
    // Test dzialania listy
    list *lista = createList();

    addElement(&lista, 1);
    addElement(&lista, 2);
    addElement(&lista, 3);
    addElement(&lista, 4);
    addElement(&lista, 5);

    showList(lista);

    deleteElement(&lista, 0);

    showList(lista);

    (*getElement(lista, 0)).value = 100;

    showList(lista);

    deleteElement(&lista, 2);

    showList(lista);

    list *l2 = createList();
    addElement(&l2, 6);
    addElement(&l2, 7);
    addElement(&l2, 8);
    addElement(&l2, 9);
    addElement(&l2, 10);

    showList(l2);

    merge(lista, &l2);
    showList(lista);
    showList(l2);

    deleteElement(&lista, 7);

    showList(lista);

    deleteElement(&lista, 0);

    showList(lista);

    deleteList(&lista);

    showList(lista);

    showList(l2);
    */

    /*
    // TEST, trzeba wykomentowac to *list2 = NULL;
    list *l3 = createList();
    addElement(&l3, 1);
    addElement(&l3, 2);
    showList(l3);
    
    list *l4 = createList();
    addElement(&l4, 3);
    addElement(&l4, 4);
    showList(l4);
    merge(l3, &l4);
    showList(l3);
    showList(l4);
    addElement(&l3, 5);
    showList(l3);
    showList(l4);
    */

    return 0;
}
