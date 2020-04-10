#include "median.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition5(int *arr, int left, int right) {
    int i = left + 1;
    while (i <= right) {
        int j = i;
        while (j > left && *(arr+j-1) > *(arr+j)) {
            swap(arr+j-1, arr+j);
            j = j-1;
        }
        i = i+1;
    }

    return (left + right)/2;
}

int pivot(int *arr, int left, int right) {
    if (right - left < 5) {
        return partition5(arr, left, right);
    }

    for (int i=left; i <= right; i++) {
        int subRight = i+4;
        if (subRight > right) {
            subRight = right;
        }
        int median5 = partition5(arr, i, subRight);
        swap(arr + median5, arr + left + ((i-left)/5));
    }

    int mid = (right - left)/10 + left + 1;
    return linear_search_median(arr, left, left + ((right-left)/5), mid);
}

int partition(int *arr, int left, int right, int pivotIndex, int n) {
    int pivotValue = *(arr+pivotIndex);
    swap(arr+pivotIndex, arr+right);
    int storeIndex = left;

    for (int i=left; i<=right-1; i++) {
        if (*(arr+i) < pivotValue) {
            swap(arr+storeIndex, arr+i);
            storeIndex++;
        }
    }

    int storeIndexEq = storeIndex;
    for (int i=storeIndex; i<=right-1; i++) {
        if (*(arr+i) == pivotValue) {
            swap(arr+storeIndexEq, arr+i);
            storeIndexEq++;
        }
    }
    swap(arr+right, arr+storeIndexEq);

    if (n < storeIndex) {
        return storeIndex;
    } else if (n <= storeIndexEq) {
        return n;
    } else {
        return storeIndexEq;
    }
}

int linear_search_median(int *arr, int left, int right, int n) {
    while (1) {
        if (left == right) {
            return left;
        } else {
            int pivotIndex = pivot(arr, left, right);
            pivotIndex = partition(arr, left, right, pivotIndex, n);
            if (n == pivotIndex) {
                return n;
            } else if (n < pivotIndex) {
                right = pivotIndex - 1;
            } else {
                left = pivotIndex + 1;
            }
        }
    }
}