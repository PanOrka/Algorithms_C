#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *left;
    void *right;
    int value;
} node;

typedef struct {
    node *head;
    node *tail;

    int size;
} list;

void addElement(list *p, int value) {
    if ((*p).head == NULL) { // wtedy cala lista jest pusta, zaczynamy od head (lewa)  H oooo T
        node *n = malloc(sizeof(node));
        node n1 = {NULL, NULL, value};
        *n = n1;
        (*p).head = n;
    } else if ((*p).tail == NULL) { // wtedy jest head a nie ma taila
        node *n = malloc(sizeof(node));
        node n1 = {(*p).head, (*p).head, value}; // zapetlamy do circular tail
        *n = n1;
        (*p).tail = n;
        (*((*p).head)).right = n; // zapetlamy do circular head
        (*((*p).head)).left = n;
    } else { // teraz juz mamy head i tail
        node *n = malloc(sizeof(node));
        node n1 = {(*p).tail, (*p).head, value};
        *n = n1;
        (*((*p).tail)).right = n; // dodajemy referencje do nowego taila w starym tailu
        (*((*p).head)).left = n; // zapetlamy do circular
        (*p).tail = n; // zastapiamy nowym tailem
    }

    (*p).size++;
}

void showLeft(list *p) {
    node *pointer = (*p).head;
    
    printf("=== LIST LEFT to RIGHT ===\n");
    while (pointer != (*p).tail) {
        printf("%d, ", (*pointer).value);
        pointer = (*pointer).right;
    }

    if (pointer != NULL) {
        printf("%d", (*pointer).value);
    }
    printf("\n==========================\n");
}

void showRight(list *p) {
    node *pointer = (*p).tail;

    printf("=== LIST RIGHT to LEFT ===\n");
    if (pointer != NULL) {

        while (pointer != (*p).head) {
            printf("%d, ", (*pointer).value);
            pointer = (*pointer).left;
        }
        printf("%d", (*pointer).value);

    } else if ((*p).head != NULL) {
        printf("%d", (*((*p).head)).value);
    }
    printf("\n==========================\n");
}

void push_right(list *p) { // swap tail i head tutaj cykl >>
    if ((*p).size >= 2) {
        (*p).head = (*p).tail;
        (*p).tail = (*((*p).head)).left;
    }
}

void push_left(list *p) { // tutaj cykl <<
    if ((*p).size >= 2) {
        (*p).tail = (*p).head;
        (*p).head = (*((*p).tail)).right;
    }
}

node * getElement(list *lista, int n) {
    int size = (*lista).size;
    if (size > 1) {
        node *el1;
        n%=size;
        if (n < 0) {
            n = size + n;
        }

        if (n >= size/2) {
            el1 = (*lista).tail;
            for (int i=size-1; i>n; i--) {
                el1 = (*el1).left;
            }
            return el1;
        } else {
            el1 = (*lista).head;
            for (int i=0; i<n; i++) {
                el1 = (*el1).right;
            }
            return el1;
        }
    } else if (size == 1) {
        return (*lista).head;
    } else {
        fprintf(stderr, "Error: List is empty\n");
        exit(1);
    }
}

void deleteElement(list *lista, int n) {
    if ((*lista).size > 1) {
        node *el1;

        n %= (*lista).size;
        if (n < 0) {
            n = (*lista).size + n;
        }

        if (n >= (*lista).size/2) { // RIGHT SIDE
            el1 = (*lista).head;
            for (int i=(*lista).size-1; i>n; i--) { // teraz dostaniemy element n+1
                el1 = (*el1).left;
            }

            node *el_n = (*el1).left; // tutaj mamy element n-ty
            node *el_k = (*el_n).left; // tutaj mamy element n-1
            (*el1).left = el_k;
            (*el_k).right = el1;
            free(el_n);

            if (n == (*lista).size-1) {
                (*lista).tail = el_k; // jak usuniemy tail to ten z lewej od starego taila staje sie tailem
            }

            (*lista).size--;
        } else { // LEFT SIDE
            el1 = (*lista).tail;
            for (int i=0; i<n; i++) { // teraz mamy n-1
                el1 = (*el1).right;
            }

            node *el_n = (*el1).right; // tutaj mamy n
            node *el_k = (*el_n).right; // tutaj mamy n+1
            (*el1).right = el_k;
            (*el_k).left = el1;
            free(el_n);

            if (n == 0) {
                (*lista).head = el_k; // jak usuniemy head to n+1 staje sie headem bo n-1 jest tailem
            }

            (*lista).size--;
        }
    } else if ((*lista).size == 1) {
        free((*lista).head);
        (*lista).head = NULL;
        (*lista).tail = NULL;
        (*lista).size--;
    } else {
        fprintf(stderr, "Error: List is empty\n");
    }
}

void deleteList(list *lista) {
    if ((*lista).size <= 1) {
        free((*lista).head);
        (*lista).head = NULL;
        (*lista).tail = NULL;
        (*lista).size = 0;
    } else {
        node *el1 = (*lista).head;
        while (el1 != (*lista).tail) {
            el1 = (*el1).right;
            free((*el1).left);
        }
        free(el1);
        (*lista).head = NULL;
        (*lista).tail = NULL;
        (*lista).size = 0;
    }
}

void merge(list *lista1, list *lista2) {
    (*((*lista1).tail)).right = (*lista2).head;
    (*((*lista2).head)).left = (*lista1).tail;

    (*((*lista1).head)).left = (*lista2).tail;
    (*((*lista2).tail)).right = (*lista1).head;

    (*lista1).tail = (*lista2).tail;

    (*lista1).size += (*lista2).size;
    (*lista2).size = 0;
    (*lista2).head = NULL;
    (*lista2).tail = NULL;
}

list * createList() {
    list *lista = malloc(sizeof(list));
    list l1 = {NULL, NULL, 0};
    *lista = l1;

    return lista;
}

int main() {
    list *lista = createList();

    for (int i=0; i < 10; i++) {
        addElement(lista, i);
    }
    showLeft(lista);

    list *l2 = createList();
    for (int i=10; i < 20; i++) {
        addElement(l2, i);
    }
    showLeft(l2);

    merge(lista, l2);
    deleteElement(lista, 14);
    showLeft(lista);
    printf("%d", (*getElement(lista, 25)).value);

    return 0;
}
