#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define N 50000000
// Function to check if number is prine

int isPrime(int n) {
    if (n < 2)
        return 0;
    for (int i = 2; i <=sqrt(n); i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    double startTime = omp_get_wtime();
    int counterPrimes = 0;

    // Parallelize loop for search primes
    #pragma omp parallel for reduction(+:counterPrimes)
    for (int i = 2; i <= N; i++) {
        if (isPrime(i))
            counterPrimes++;
    }

    double elapsedTime = omp_get_wtime() - startTime;

    printf("Primes found: %d\n", counterPrimes);
    printf("Parallel Time: %.3fsg\n", elapsedTime);
}

// Execution: OMP_NUM_THREADS=6 ./primes_number_parallel
