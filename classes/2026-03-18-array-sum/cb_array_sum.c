#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <omp.h>

#define N 1000000000

void fill_array(int *arr, int size) {
    for (int i = 0; i < size; i++)
    {
        *(arr + i) = (N % 10) + i + 1;
    }
    
}

void sum_array(int *arr, int size, long int *result_sum) {
    *result_sum = 0;

    for (int i = 0; i < size; i++)
    {
        *result_sum += *(arr + i);
    }
}


int main () {
    int *arr = (int *) malloc (N * sizeof(int));
    long int result_sum;


    clock_t start_time = clock();

    // fill array
    fill_array(arr, N);

    // Sum sequential
    sum_array(arr, N, &result_sum);

    // Free memory
    free(arr);
    
    // Results
    double elapsed_time = (double) (clock() - start_time) / CLOCKS_PER_SEC;


    printf("Array Elements: %d\n", N);
    printf("Total Sum: %ld\n", result_sum);
    printf("Elapsed Time: %.3fsg\n", elapsed_time);

}