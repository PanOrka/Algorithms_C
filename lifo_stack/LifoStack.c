#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *p;
    int value;
} stack;

void put(stack **p, int value) {
    stack *p2 = malloc(sizeof(stack));
    stack el1 = {*p, value};
    *p2 = el1;
    *p = p2;
}

int get(stack **p) {
    if (*p != NULL) {
        stack temp = **p;

        free(*p);
        *p = temp.p;

        return temp.value;
    }

    fprintf(stderr, "nothing on stack\n");
    return -1;
}

stack * createStack() {
    return NULL;
}

int main() {
    stack *lifo = createStack();

    get(&lifo);
    put(&lifo, 1);
    put(&lifo, 2);
    put(&lifo, 3);
    put(&lifo, 4);
    put(&lifo, 5);

    printf("%d\n", get(&lifo));
    printf("%d\n", get(&lifo));
    printf("%d\n", get(&lifo));

    put(&lifo, 6);
    put(&lifo, 7);
    put(&lifo, 8);
    put(&lifo, 9);
    
    printf("%d\n", get(&lifo));
    printf("%d\n", get(&lifo));
    printf("%d\n", get(&lifo));
    printf("%d\n", get(&lifo));
    printf("%d\n", get(&lifo));
    printf("%d\n", get(&lifo));
    printf("%d\n", get(&lifo));

    return 0;
}
