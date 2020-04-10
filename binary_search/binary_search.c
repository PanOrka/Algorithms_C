#include <stdio.h>
#include <stdlib.h>

int binary_search(int *arr, int size, int v) {
    if (size == 0) {
        return 0;
    }

    int value = *(arr+size/2);
    if (value == v) {
        return 1;
    } else if (value > v) {
        return binary_search(arr, size/2, v);
    }

    return binary_search(arr+1+(size/2), (size-1)/2, v); // else: value < v
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int size = atoi(argv[1]);
        int *arr = malloc(sizeof(int)*size);
        int v;

        for (int i=0; i<size; i++) {
            scanf("%d", arr+i);
        }
        scanf("%d", &v);

        int answer = binary_search(arr, size, v);

        printf("%d\n", answer);
    } else {
        printf("Bad amount of input data");
    }
}