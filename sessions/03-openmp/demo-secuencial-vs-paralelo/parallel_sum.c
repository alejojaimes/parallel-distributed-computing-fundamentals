#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000000L

int main() {
    long i;
    double sum = 0.0;
    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < N; i++) {
        sum += 1.0;
    }

    end = omp_get_wtime();

    printf("Parallel sum result: %.2f\n", sum);
    printf("Number of threads used: %d\n", omp_get_max_threads());
    printf("Parallel time: %.4f seconds\n", end - start);

    return 0;
}
