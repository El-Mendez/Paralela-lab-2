#include <omp.h>
#define ARRAY_SIZE_THRESHOLD 50

void swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void quickSortSeq(int data[], int len) {
    if (len <= 1) {
        return;
    }

    int pivot = data[len-1];
    int lower = 0;
    int upper = len-2;

    while (lower <= upper) {
        while (lower <= upper && data[lower] < pivot)
            lower++;
        while (lower <= upper && pivot < data[upper])
            upper--;

        if (lower <= upper) {
            swap(data + lower, data + upper);
            lower++;
            upper--;
        }
    }

    // move the pivot to the appropriate location
    swap(data + lower, data + len-1);

    quickSortSeq(data, lower);
    quickSortSeq(data + lower + 1, len - lower - 1);
}

void quickSortParallel(int data[], int len) {
    if (len <= 1) {
        return;
    }

    if (len < ARRAY_SIZE_THRESHOLD) {
        quickSortSeq(data, len);
    }

    int pivot = data[len-1];
    int lower = 0;
    int upper = len-2;

    while (lower <= upper) {
        while (lower <= upper && data[lower] < pivot)
            lower++;
        while (lower <= upper && pivot < data[upper])
            upper--;

        if (lower <= upper) {
            swap(data + lower, data + upper);
            lower++;
            upper--;
        }
    }

    // move the pivot to the appropriate location
    swap(data + lower, data + len-1);

    #pragma omp task default(none) private(lower) shared(data)
    quickSortParallel(data, lower);

    #pragma omp task default(none) private(lower, len) shared(data)
    quickSortParallel(data + lower + 1, len - lower - 1);
}
