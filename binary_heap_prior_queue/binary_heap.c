#include <stdlib.h>
#include <stdio.h>

#include "binary_heap.h"

#define INC_MAX_SIZE 20
#define parent(i) ((i-1)/2)
#define left(i) ((i+1)*2 - 1)
#define right(i) ((i+1)*2)


heap * create_heap(int max_size) {
    if (max_size > 0) {
        heap *h = malloc(sizeof(heap));
        h->tab = malloc(sizeof(node)*max_size);
        h->used_size = 0;
        h->max_size = max_size;

        return h;
    } else {
        return NULL;
    }
}

void insert(heap *h, int value, int priority) {
    if (h->used_size < h->max_size) {
        int i = h->used_size;
        while (i>0 && (h->tab + parent(i))->priority > priority) {
            *(h->tab + i) = *(h->tab + parent(i));
            i = parent(i);
        }
        (h->tab + i)->value = value;
        (h->tab + i)->priority = priority;

        h->used_size += 1;
    } else {
        node *temp_ptr = h->tab;
        h->tab = malloc(sizeof(node)*(h->max_size + INC_MAX_SIZE)); // powiekszamy max_size
        for (int i=0; i<h->max_size; i++) {
            *(h->tab + i) = *(temp_ptr + i);
        }
        h->max_size += INC_MAX_SIZE;

        free(temp_ptr);
        insert(h, value, priority);
    }
}

int is_empty(heap *h) {
    if (h->used_size == 0) {
        return 1;
    } else {
        return 0;
    }
}

void top(heap *h) {
    if (is_empty(h)) {
        printf("\n");
    } else {
        printf("%d\n", (h->tab)->value);
    }
}

void swap(node *ptr_1, node *ptr_2) {
    node temp_node = *ptr_1;
    *ptr_1 = *ptr_2;
    *ptr_2 = temp_node;
}

void pop(heap *h) {
    if (is_empty(h)) {
        printf("\n");
    } else {
        printf("%d\n", (h->tab)->value);
        h->used_size--;
        if (h->used_size > 0) {
            *(h->tab) = *(h->tab + h->used_size);
            int i = 0;
            while (left(i) < h->used_size) {
                int k;
                if (right(i) < h->used_size) {
                    if ((h->tab + left(i))->priority <= (h->tab + right(i))->priority) {
                        k = left(i);
                    } else {
                        k = right(i);
                    }
                } else {
                    k = left(i);
                }

                if ((h->tab + i)->priority > (h->tab + k)->priority) {
                    swap((h->tab + i), (h->tab + k));
                    i = k;
                } else {
                    return;
                }
            }
        }
    }
}

void change_priority(heap *h, int value, int new_priority) {
    for (int i=0; i<h->used_size; i++) {
        if ((h->tab + i)->value == value && (h->tab + i)->priority > new_priority) {
            (h->tab + i)->priority = new_priority;
            int k = i;
            while (k>0 && (h->tab + parent(k))->priority > (h->tab + k)->priority) {
                swap((h->tab + parent(k)), (h->tab + k));
                k = parent(k);
            }
        }
    }
}

void print(heap *h) {
    for (int i=0; i<h->used_size; i++) {
        printf("(%d, %d), ", (h->tab + i)->value, (h->tab + i)->priority);
    }
    printf("\n");
}
