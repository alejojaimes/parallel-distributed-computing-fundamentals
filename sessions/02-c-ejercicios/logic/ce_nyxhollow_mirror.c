/**
 * @file ce_nyxhollow_mirror.c
 * @brief ---
 * @author Alejandro Jaimes
 * @date 2026-09-21
 */

#include <stdio.h>
#include <stdlib.h>

#define N 3

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void bubble_sort(int *arr, int size, int *count_swaps) {
    for (int i = 0; i < size; i++) {
        for (int j = (i + 1); j< size; j++) {
            if (*(arr + i) > *(arr + j)) {
                swap((arr + i), (arr +j));
                (*count_swaps)++;
            }
        }
    }
}

int get_fracture(int number) {
    int copy = number;
    int fracture = 0;
    while(number > 0) {
        int tmp = number % 10;
        fracture = fracture * 10 + tmp;
        number /= 10;
    }
    return abs(copy - fracture);
}

void fill_array_with_fracture(int *arr_sorted, int *arr_fracture, int size) {
    for (int i = 0; i<size; i++) {
        *(arr_fracture + i) = get_fracture(*(arr_sorted + i));
    }
}

void fill_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            *(arr + i) = ((i * i * i) % 100) + 10;
        } else {
            *(arr + i) = ((i * i * i) % 10) + 75;
        }
    }
}

void print_array(int *arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        if (i == (size - 1)) {
            printf("%d]\n", *(arr + i));
            break;
        }
        printf("%d,", *(arr + i));
    }
}

int reduce_array(int *arr, int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result += *(arr + i);
    }
    return result;
}

int main() {
    int count_swaps  = 0;
    int size = N;
    int *arr = (int *) malloc (size * sizeof(int));
    int *arr_frac = (int *) malloc (size * sizeof(int));
    //
    if (arr == NULL && arr_frac == NULL) {
        return 1;
    }
    //
    fill_array(arr, N);
    //
    printf("=====ORIGINAL ARRAY===========\n");
    print_array(arr, N);
    bubble_sort(arr,size,&count_swaps);
    printf("=====SORTED ARRAY===========\n");
    print_array(arr, N);
    fill_array_with_fracture(arr, arr_frac, size);
    printf("=====FRACTURED ARRAY===========\n");
    print_array(arr_frac, N);
    printf("=====SWAPS===========\n");
    printf("%d\n", count_swaps);
    printf("=====THRESHOLD===========\n");
    int threshold = (count_swaps + 1) * 50;
    printf("%d\n", threshold);
    printf("=====VEREDICT===========\n");
    int total_fracture = reduce_array(arr_frac, size);
    if (total_fracture> threshold) {
        printf("Total Fractures: %d\tThreshold: %d\n", total_fracture, threshold);
        printf("El espejo se rompe.\n");
    } else {
        printf("Total Fractures: %d\tThreshold: %d\n", total_fracture, threshold);
        printf("El espejo resiste.\n");
    }

    free(arr);
    free(arr_frac);

}
