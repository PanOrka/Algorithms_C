#include <math.h>

#include "randomizer.h"
#include "linear_search.h"
#include "select_algorithm.h"
#include "displayer.h"

void select_start(int *arr, int size, int kth) {
    arr_to_display = arr;
    size_of_display = size;
    k_place = kth;

    if (kth == 1) {
        linear_search_min(arr, size);
    } else if (kth == size) {
        linear_search_max(arr, size);
    } else {
        select_search(arr, size, kth);
    }

    display_arr(stdout);
}

int find_min(int *arr, int size) {
    int min = *arr;
    for (int i=1; i<size; i++) {
        if (*(arr+i) < min) {
            min = *(arr+i);
        }
    }

    return min;
}

int find_max(int *arr, int size) {
    int max = *arr;
    for (int i=1; i<size; i++) {
        if (*(arr+i) > max) {
            max = *(arr+i);
        }
    }

    return max;
}

double find_avg(int *arr, int size) {
    int sum = 0;
    for (int i=0; i<size; i++) {
        sum += *(arr+i);
    }

    return (double)sum/(double)size; 
}

double find_std(int *arr, int size, double avg) {
    double sum = 0;
    for (int i=0; i<size; i++) {
        double temp = (double)(*(arr+i) - avg);
        sum += temp*temp;
    }
    return sqrt(sum/(double)size);
}

void take_data(int data_n) {
    int *all_trans = malloc(sizeof(int)*data_n);
    int *all_comp = malloc(sizeof(int)*data_n);
    int size, kth;
    scanf("%d", &size);
    scanf("%d", &kth);
    for (int i=0; i<data_n; i++) {
        trans = 0;
        comp = 0;
        int *arr = random_data(size);
        select_start(arr, size, kth);
        free(arr);
        *(all_trans+i) = trans;
        *(all_comp+i) = comp;
    }
    int trans_min = find_min(all_trans, data_n);
    int trans_max = find_max(all_trans, data_n);

    int comp_min = find_min(all_comp, data_n);
    int comp_max = find_max(all_comp, data_n);

    double trans_avg = find_avg(all_trans, data_n);
    double comp_avg = find_avg(all_comp, data_n);

    double trans_std = find_std(all_trans, data_n, trans_avg);
    double comp_std = find_std(all_trans, data_n, comp_avg);

    printf("TRANSPOZYCJE: min = %d, max = %d, AVG = %f, STD = %f\n", trans_min, trans_max, trans_avg, trans_std);
    printf("KOMPARYCJE: min = %d, max = %d, AVG = %f, STD = %f\n", comp_min, comp_max, comp_avg, comp_std);
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        if (strcmp(argv[1], "-r") == 0) {
            int size, kth;
            scanf("%d", &size);
            scanf("%d", &kth);
            int *arr = random_data(size);
            select_start(arr, size, kth);
        } else if (strcmp(argv[1], "-p") == 0) {
            int size, kth;
            scanf("%d", &size);
            scanf("%d", &kth);
            int *arr = random_permutation(size);
            select_start(arr, size, kth);
        } else {
            fprintf(stderr, "Wrong argument\n");
            exit(1);
        }
    } else if (argc == 3) {
        int data_n = atoi(argv[2]);
        take_data(data_n);
    } else {
        fprintf(stderr, "Wrong amount of arguments\n");
        exit(1);
    }
}