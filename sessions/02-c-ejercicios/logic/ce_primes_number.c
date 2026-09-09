#include <stdio.h>
#include <math.h>
#include <time.h>

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
    clock_t startTime = clock();
    int counterPrimes = 0;

    for (int i = 2; i <= N; i++) {
        if (isPrime(i)) 
            counterPrimes++;
    }


    double elapsedTime = (double) (clock() - startTime) / CLOCKS_PER_SEC;

    printf("Primes found: %d\n", counterPrimes);
    printf("Sequential Time: %.3fsg\n", elapsedTime);
}