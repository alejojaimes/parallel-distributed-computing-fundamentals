/**
 * Exercise 4: Parallel Matrix Row Sum
 * Brief: Write a program that computes the sum of each row in a matrix 2D
 * in parallel using OpenMP. The program should initialize a matrix with
 * random values, compute the row sums in parallel.
 * Question: How does the performance of the parallel version compare to a sequential version?
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ROWS 6000
#define COLS 6000

// The sums are repeated a few times so the timing is stable and the cost of
// creating the parallel region is amortized.
#define REPEATS 15

// The matrix is stored as a flat array: element (r, c) is at r * COLS + c.
void fill_matrix(int *matrix) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            *(matrix + r * COLS + c) = rand() % 100;
        }
    }
}

// Sequential: one row after another.
void row_sums_sequential(const int *matrix, long long *row_sum) {
    for (int k = 0; k < REPEATS; k++) {
        for (int r = 0; r < ROWS; r++) {
            long long sum = 0;
            for (int c = 0; c < COLS; c++) {
                sum += *(matrix + r * COLS + c);
            }
            *(row_sum + r) = sum;
        }
    }
}

// Parallel: rows are independent, so OpenMP can hand a block of rows to
// each thread. Every row_sum[r] is written by exactly one thread -> no race.
void row_sums_parallel(const int *matrix, long long *row_sum) {
    for (int k = 0; k < REPEATS; k++) {
        #pragma omp parallel for schedule(static)
        for (int r = 0; r < ROWS; r++) {
            long long sum = 0;
            for (int c = 0; c < COLS; c++) {
                sum += *(matrix + r * COLS + c);
            }
            *(row_sum + r) = sum;
        }
    }
}

int main() {
    srand(42);

    int *matrix       = malloc((size_t)ROWS * COLS * sizeof(int));
    long long *row_seq = malloc((size_t)ROWS * sizeof(long long));
    long long *row_par = malloc((size_t)ROWS * sizeof(long long));

    if (!matrix || !row_seq || !row_par) {
        printf("Out of memory\n");
        return 1;
    }

    fill_matrix(matrix);

    double t0 = omp_get_wtime();
    row_sums_sequential(matrix, row_seq);
    double t_seq = omp_get_wtime() - t0;

    t0 = omp_get_wtime();
    row_sums_parallel(matrix, row_par);
    double t_par = omp_get_wtime() - t0;

    // Both versions must produce the same row sums.
    int mismatch = 0;
    for (int r = 0; r < ROWS; r++) {
        if (*(row_seq + r) != *(row_par + r)) {
            mismatch++;
        }
    }

    printf("Matrix %dx%d, threads = %d\n", ROWS, COLS, omp_get_max_threads());
    printf("row_sum[0] = %lld, row_sum[%d] = %lld\n",
           *row_par, ROWS - 1, *(row_par + ROWS - 1));
    printf("Mismatches sequential vs parallel: %d\n", mismatch);
    printf("Time sequential = %.4f s  (%d passes)\n", t_seq, REPEATS);
    printf("Time parallel   = %.4f s  (%d passes)\n", t_par, REPEATS);
    if (t_par > 0.0) {
        // Answer to the question: the parallel version is faster, but the
        // speedup stays well below the thread count. A plain row sum is
        // memory-bandwidth bound: all threads read from the same RAM and
        // saturate the memory bus long before the cores run out of work.
        // Replace the inner "sum += v" with real per-element computation and
        // the speedup gets much closer to the number of cores.
        printf("Speedup = %.2fx  (with %d threads)\n",
               t_seq / t_par, omp_get_max_threads());
    }

    free(matrix);
    free(row_seq);
    free(row_par);
    return 0;
}
