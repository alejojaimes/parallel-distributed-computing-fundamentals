/**
 * @file cb_pointers_02.c
 * @brief Swap values using pointers.
 * @author Alejandro Jaimes
 * @date 2026-09-09
 */
#include <stdio.h>

void swap(int *number_a, int *number_b) {
    int ptr_tmp = *number_a;
    //swap b value by a value
    *number_a = *number_b;
    *number_b = ptr_tmp;
}

int main () {
    int number_a = 52, number_b = 23;
    printf("A: \tValue: %d\tAddr Location: %p\n", number_a, &number_a);
    printf("B: \tValue: %d\tAddr Location: %p\n", number_b, &number_b);
    printf("\n-----------------CHANGE----------------------\n");
    swap(&number_a, &number_b);
    printf("A: \tValue: %d\tAddr Location: %p\n", number_a, &number_a);
    printf("B: \tValue: %d\tAddr Location: %p\n", number_b, &number_b);

    return 0;
}
