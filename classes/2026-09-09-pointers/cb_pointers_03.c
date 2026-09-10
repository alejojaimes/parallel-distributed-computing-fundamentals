/**
 * @file cb_pointers_03.c
 * @brief Fill array with dynamic memory using random numbers, for this case N = 8;
 * @author Alejandro Jaimes
 * @date 2026-09-09
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# define N 8

void print_array(int *arr) {
    printf("[");
    for (int i = 0; i < N; i++) {
        if (i == (N - 1)) {
            printf("%d]\n", *(arr + i));
            break;
        }
        printf("%d,", *(arr + i));
    }
}

int main() {
    // Dynamic array
    int *arr = (int *) malloc (N * sizeof(int));
    //Random numbers
    // seed
    srand(time(NULL));
    for (int i = 0; i<N; i++) {
        int rand_number = rand()  % 100 ; // [0-100]
        *(arr + i) = rand_number;
    }
    print_array(arr);
    free(arr);
    return 0;
}
