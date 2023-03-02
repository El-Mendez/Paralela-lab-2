#include <iostream>
#include <cstdlib>
#include <omp.h>

#include "saveToFile.h"
#include "quickSort.h"

#define DEFAULT_AMOUNT 10'000'000;
#define NUMBERS_LOCATION "../out/numbers.csv"
#define SORTED_LOCATION "../out/sorted.csv"
#define THREAD_AMOUNT 8

// comentar para volver al programa secuencial
#define PARALLEL

#ifdef PARALLEL
void quickSort(int data[], int len) {
    #pragma omp parallel default(none) shared(data, len) num_threads(THREAD_AMOUNT)
    #pragma omp single nowait
    quickSortParallel(data, len);
}
#else
void quickSort(int data[], int len) {
    quickSortSeq(data, len);
}
#endif

int main(int argc, char** argv) {
    int seed = time(nullptr);
    srand(seed);
    std::cout << "seed: " << seed << "\n";

    double start, end;

    int amount = DEFAULT_AMOUNT;
    if (argc == 2) {
        amount = std::atoi(argv[1]);
    }

    // because it's a number way too big, we can't allocate it on the stack.
    generateNumbers(amount, NUMBERS_LOCATION);

    int *numbers = new int[amount];
    readNumbers(numbers, amount, NUMBERS_LOCATION);

    start = omp_get_wtime();
    quickSort(numbers, amount);
    end = omp_get_wtime();

    saveNumbers(numbers, amount, SORTED_LOCATION);
    delete[] numbers;

    std::cout << "Time(s): " << end - start << "\n";
    return 0;
}
