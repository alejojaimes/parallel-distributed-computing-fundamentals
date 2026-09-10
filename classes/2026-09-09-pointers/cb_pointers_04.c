/**
 * @file cb_pointers_04.c
 * @brief Calculate multiply for each number of list using aritmethic of pointers
 * @author Alejandro Jaimes
 * @date 2026-09-09
 */
#include <stdio.h>
#include <stdlib.h>

void multiply_element_by_list(int *arr, int size, int *ptr_arr, int n) {
    //iterate over each element to multiply arr[i] * n
    // check null pointer validation
    if (ptr_arr == NULL) {
        printf("Failed initialization of pointer.");
    }
    for (int i = 0; i< size; i++) {
        //printf("%d", (*(arr + i) * n));
        *(ptr_arr ++) = *(arr + i) * n;
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

int main () {
    // Declare array
    int arr [5] = {5, 8, 9, 12, 3};
    int n = 2;
    int size = sizeof(arr) / sizeof(arr[0]);
    // Declare dynamic memory
    int *ptr_arr = (int *) malloc (size * sizeof(int));
    // Implements
    print_array(arr, size);
    multiply_element_by_list(arr, size, ptr_arr, n);
    print_array(ptr_arr, size);
    // Free
    free(ptr_arr);
    // Finish
    return 0;
}
