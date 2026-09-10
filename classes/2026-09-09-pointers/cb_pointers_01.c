/**
 * @file cb_pointers_01.c
 * @brief Basic Exercise of pointers in C.
 * @author Alejandro Jaimes
 * @date 2026-09-09
 */
#include <stdio.h>

int main () {
    int number = 5;
    int *ptr_number = &number;
    printf("Value: %d\tAddr Location: %p\n", number, &number);
    printf("Value: %d\tAddr Location: %p", *ptr_number, (void*) ptr_number);
    printf("\n----------------------------------------------\n");
    *ptr_number = 56;
    printf("Value: %d\tAddr Location: %p\n", number, &number);
    printf("Value: %d\tAddr Location: %p", *ptr_number, (void*) ptr_number);
    printf("\n----------------------------------------------\n");
    ptr_number++;
    printf("Value: %d\tAddr Location: %p\n", number, &number);
    printf("Value: %d\tAddr Location: %p", *ptr_number, (void*) ptr_number);
    return 0;
}
