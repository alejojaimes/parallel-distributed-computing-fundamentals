#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000000L

int main() {
    long i;
    double sum = 0.0;
    clock_t start, end;

    start = clock();

    for (i = 0; i < N; i++) {
        sum += 1.0;
    }

    end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Sequential sum result: %.2f\n", sum);
    printf("Sequential time: %.4f seconds\n", time_spent);

    return 0;
}
