#include <string.h>
#include <stdio.h>

#include "binary_heap.h"

int main() {
    heap *h = create_heap(5);

    int lines;
    char command[10];

    scanf("%d", &lines);
    for (int i=0; i<lines; i++) {
        scanf("%s", command);

        if (strcmp(command, "insert") == 0) {
            int x, p;
            scanf("%d", &x);
            scanf("%d", &p);
            insert(h, x, p);
        } else if (strcmp(command, "empty") == 0) {
            printf("%d\n", is_empty(h));
        } else if (strcmp(command, "top") == 0) {
            top(h);
        } else if (strcmp(command, "pop") == 0) {
            pop(h);
        } else if (strcmp(command, "priority") == 0) {
            int x, p;
            scanf("%d", &x);
            scanf("%d", &p);
            change_priority(h, x, p);
        } else if (strcmp(command, "print") == 0) {
            print(h);
        }
    }
}
