/**
 * Exercise 3: Array Initialization by Thread Range
 * Brief: Write a program that initializes an array based on its ID.
 * Introduces manual work partitioning with pointers.
 * Question: What happens is N is not divisible by NTHREADS? Which positions are
 * left uninitialized?
 */

#include <stdio.h>
#include <omp.h>

#define N 12
#define NTHREADS 3

#define UNSET (-1)

int main () {
    int array[N];

    // Sentinel value so we can detect positions that no thread touched.
    for (int i = 0; i < N; i++) {
        *(array + i) = UNSET;
    }

    omp_set_num_threads(NTHREADS);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int nthreads  = omp_get_num_threads();

        // Naive partitioning: every thread takes the same chunk size.
        // When N % nthreads != 0 the last (N % nthreads) positions are never
        // assigned to any thread, so they stay UNSET.
        int chunk_size = N / nthreads;
        int start = thread_id * chunk_size;
        int end   = start + chunk_size;

        // Each thread writes its own id into the range it owns.
        for (int i = start; i < end; i++) {
            *(array + i) = thread_id;
        }

        printf("Thread %d/%d -> initialized range [%d, %d)\n",
               thread_id, nthreads, start, end);
    }

    // Show the result and report the positions left uninitialized.
    int uninitialized = 0;
    printf("\narray = [ ");
    for (int i = 0; i < N; i++) {
        printf("%d ", *(array + i));
        if (*(array + i) == UNSET) {
            uninitialized++;
        }
    }
    printf("]\n");

    // Answer to the question: with N=12 and NTHREADS=3 the division is exact,
    // so nothing is left out. Try N=13 (or NTHREADS=5) and the last
    // (N % NTHREADS) positions stay at UNSET, because only the remainder-free
    // block [0, chunk_size * NTHREADS) is covered.
    printf("Uninitialized positions: %d  (N=%d, NTHREADS=%d, N %% NTHREADS = %d)\n",
           uninitialized, N, NTHREADS, N % NTHREADS);

    return 0;
}
