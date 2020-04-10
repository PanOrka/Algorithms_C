#include "select_algorithm.h"
#include "displayer.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int *arr, int size) {
    int key, j, temp_to_show_transposition;
    for (int i = 1; i < size; i++) {
        key = *(arr + i);
        j = i - 1;
        while (j >= 0 && *(arr + j) > key) {
            comp++;
            display_comparision(*(arr + j), key);
            temp_to_show_transposition = *(arr+j+1); // JUST FOR LOG
            *(arr + j + 1) = *(arr + j);
            trans++;
            display_transposition(temp_to_show_transposition, *(arr + j));
            j = j - 1;
        }
        if (j >= 0) { // jak petla nie weszla a spelnilismy warunek 1 to bylo porownanie
            comp++;
            display_comparision(*(arr + j), key);
        }
        temp_to_show_transposition = *(arr+j+1); // JUST FOR LOG
        *(arr + j + 1) = key;
        trans++;
        display_transposition(temp_to_show_transposition, key);
    }
}

int find_pivot(int *arr, int size) {
    if (size > 5) {
        int i, place_swap = 0;
        for (i=0; i<size/5; i++) {
            insertion_sort(arr+i*5, 5);
            swap(arr+place_swap, arr+i*5+2); // 1 2 [3] 4 5
            place_swap++;
            trans++;
            display_transposition(*(arr+place_swap), *(arr+i*5+2));
        }

        if (size%5 > 0) {
            insertion_sort(arr+i*5, size%5);
            swap(arr+place_swap, arr+i*5+(((size%5)-1)/2));
            place_swap++;
            trans++;
            display_transposition(*(arr+place_swap), *(arr+i*5+(((size%5)-1)/2)));
        }
        return find_pivot(arr, place_swap);
    } else if (size == 5) {
        insertion_sort(arr, size);
        return 2;
    } else {
        insertion_sort(arr, size);
        return ((size%5)-1)/2;
    }
}

int partition(int *arr, int size, int pivot) {
    display_arr(stderr);

    int swap;
    swap = *(arr+pivot);
    display_pivot(swap);
    *(arr+pivot) = *(arr+size-1);
    *(arr+size-1) = swap;
    trans++;
    display_transposition(swap, *(arr+pivot));

    int div_p = *(arr+size-1); // biore div_p jako ostatni element tablicy, zawsze
    int index_left = 0;
    int index_right = size-2;

    while (index_left < index_right) { // to nasz warunek, robie na dwa "pointery"
        comp++;
        display_comparision(*(arr+index_left), div_p);
        if (*(arr+index_left) > div_p) {
            while (index_left < index_right) {
                comp++;
                display_comparision(*(arr+index_right), div_p);
                if (*(arr+index_right) <= div_p) {
                    swap = *(arr+index_right);
                    *(arr+index_right) = *(arr+index_left);
                    *(arr+index_left) = swap;
                    index_right--;
                    index_left++;
                    goto END; // jesli udal sie swap to robimy "break"
                } else {
                    index_right--;
                }
            }
            goto SWAP; // jesli nie bylo goto END to wtedy while() skonczyl sie na index_left == index_right i wiemy ze *(elements+index_right) <= div_p wiec mozemy swap
END:        trans++;
            display_transposition(*(arr+index_right+1), *(arr+index_left-1));
        } else {
            index_left++;
        }
    }

    comp++;
    display_comparision(*(arr+index_left), div_p);
    if (*(arr+index_left) > div_p) {
SWAP:   *(arr+size-1) = *(arr+index_left);
        *(arr+index_left) = div_p;
        index_left--;
        trans++;
        display_transposition(*(arr+size-1), div_p);
    } else { // w tym wypadku skonczylismy na ostatniej mniejszej lub rownej od div_p wiec swapujemy kolejna z div_p
        *(arr+size-1) = *(arr+index_left+1); // czasami swapniemy div_p z samym soba, probowalem jakos to zrobic ale jednak zostalo :(
        *(arr+index_left+1) = div_p;
        trans++;
        display_transposition(*(arr+size-1), div_p);
    }

    display_rest();

    return index_left+1;
}

void select_search(int *arr, int size, int kth) {
    if (size <= 1) {
        return;
    } else if (size <= 6) {
        insertion_sort(arr, size);
    } else {
        int pivot = find_pivot(arr, size);
        pivot = partition(arr, size, pivot);

        if (pivot+1 == kth) {
            return;
        } else if (kth < pivot+1) {
            select_search(arr, pivot, kth);
        } else {
            select_search(arr+pivot+1, size-pivot-1, kth - (pivot+1));
        }
    }
}