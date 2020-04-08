#include <stdio.h>
#include <stdlib.h>

int find_max(int *arr, int arr_size) {
    int max = *arr;

    for (int i=1; i<arr_size; i++) {
        if (max < *(arr + i)) {
            max = *(arr + i);
        }
    }

    return max;
}

int * radix_sort(int *arr, int arr_size) {
    int *buffer[2];
    buffer[0] = arr;
    buffer[1] = malloc(sizeof(int)*arr_size);
    int copy_counter = 0;

    int max = find_max(arr, arr_size);

    for (int i=1; i < max; i *= 10) {
        int count[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // stack allocated

        for (int k=0; k<arr_size; k++) { // pierw dzielimy buckety
            count[(*(buffer[copy_counter] + k)/i)%10 + 1]++;
        }

        for (int k=1; k<10; k++) {
            count[k] += count[k-1];
        }

        for (int k=0; k<arr_size; k++) {
            int temp = *(buffer[copy_counter] + k);

            *(buffer[(copy_counter+1)%2] + count[(temp/i)%10]) = temp;
            count[(temp/i)%10]++;
        }
        copy_counter = (copy_counter+1)%2;
    }

    free(buffer[(copy_counter+1)%2]);
    return buffer[copy_counter];
}

void run_normal() {
    int arr_size;

    printf("Welcome in RadixSort, enter size of data:");
    scanf("%d", &arr_size);
    printf("Enter %d elements\n", arr_size);
    
    int *arr = malloc(sizeof(int)*arr_size);
    for (int i=0; i<arr_size; i++) {
        scanf("%d", arr+i);
    }

    int *sorted = radix_sort(arr, arr_size);
    arr = NULL;

    for (int i=0; i<arr_size; i++) {
        printf("%d, ", *(sorted + i));
    }
}

int main() {
    run_normal();
}