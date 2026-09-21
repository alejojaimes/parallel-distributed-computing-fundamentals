/**
 * @file cb_array_sum.c
 * @brief Sums the elemnts of a dynamic array using pointer arithmetic
 * @author Alejandro Jaimes
 * @date 2026-09-21
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 200000000

long long sum_pointers_array(int *arr, int size) {
    long long total_sum = 0;
    for (int i = 0; i < size; i++) {
        total_sum += *(arr + i);
    }
    return total_sum;
}

void fill_array(int *arr, int size){
    for (int i = 0; i < size; i++) {
        *(arr +  i) = i % 100;
    }
}

int main() {
    // 1. Create array with dynamic memory
    int size = N;
    int *arr = (int *) malloc( size  * sizeof(int));
    // 2. Check if the pointer is not null (validation only)
    if (arr == NULL) {
        printf("No hay suficiente memoria, para N = %d", size);
        return 1;
    }
    // 3. fill array
    fill_array(arr, size);
    // 4. Return total sum of array
    clock_t start_time = clock(); // start time
    long long total_sum = sum_pointers_array(arr, size);
    // 5. Measurement time between fill_array and print_array
    double elapsed_time = (double) (clock() - start_time) / CLOCKS_PER_SEC; // finisth_time - start_time
    // 6. Print results
    printf("Total Sum: %lld\n", total_sum);
    printf("Size: %d\n", size);
    printf("Sequential time: %.3fsg\n", elapsed_time);
    // 7. Free memory
    free(arr);
    return 0;
}
