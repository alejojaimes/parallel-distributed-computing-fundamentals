#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000000
#define MAX_THREADS 64

void fill_array(int *arr, int size) {
    for (int i = 0; i < size; i++)
    {
        *(arr + i) = i + 1;
    }
}

void sum_array_parallel(int *arr, int size, long long *result_sum) {
    long long tmp_value = 0;
    #pragma omp parallel for reduction (+:tmp_value)
    for (int i = 0; i < size; i++)
    {
        tmp_value += *(arr + i);
    }
        
    *result_sum = tmp_value;
}

int main() {
    int *arr = (int *) malloc(N * sizeof(int));
    long long result_sum = 0;

    double start_time = omp_get_wtime();

    fill_array(arr, N);
    sum_array_parallel(arr, N, &result_sum);

    double elapsed_time = omp_get_wtime() - start_time;

    free(arr);

    printf("Array Elements : %d\n",     N);
    printf("Total Sum      : %lld\n",   result_sum);
    printf("Parallel Time  : %.3fsg\n", elapsed_time);

    return 0;
}