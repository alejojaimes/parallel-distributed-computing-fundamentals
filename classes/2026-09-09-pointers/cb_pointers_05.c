/**
 * @file cb_pointers_05.c
 * @brief inverse array using aritmethic pointers
 * @author Alejandro Jaimes
 * @date 2026-09-09
 */

#include <stdio.h>
#include <stdlib.h>

#define N 10

void swap_order_arr(int *arr, int *inverse_arr) {
    int limit = 0;
    while(limit < N) {
        *(inverse_arr ++) = *(arr + (N - limit - 1));
        limit++;
    }
}

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

void fill_array(int *arr) {
    // Apply formula
    // i % 2 == 0 Then i+2
    // else == 0 Then i+6
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            //1,3,5
            *(arr + i) = i + 2;
        } else {
            *(arr + i) = i + 6;
        }
    }
}


int main() {
    int *arr = (int *) malloc (N * sizeof(int));
    int *inverse_arr = (int *) malloc (N * sizeof(int));
    fill_array(arr);
    printf("\n---------------ORIGINAL------------------------\n");
    print_array(arr);
    swap_order_arr(arr, inverse_arr);
    printf("\n---------------INVERSE----------------------\n");
    print_array(inverse_arr);
    free(arr);
    free(inverse_arr);
    return 0;
}
