#include <stdio.h>
#include <stdlib.h>

/*
Make an algorithm to reverse array
using pointers to make its possible.
*/
void reverseArray(int *pfirst, int *pend) {
    int counter = 1;
    while(pfirst < pend) {
        int tmp = *pfirst;
        printf("\n=== ITERATE %d ===\n", counter);
        printf("\nBefore Swap\n");
        printf("pfirst = %d, pend = %d, tmp = %d\n", *pfirst, *pend, tmp);

        *pfirst = *pend;
        *pend = tmp;
        printf("\nAfter Swap\n");
        printf("pfirst = %d, pend = %d, tmp = %d\n", *pfirst, *pend, tmp);

        pfirst++;
        pend--;
        counter++;        
    }
}

void printArray(int *arr, int size) {
    for(int i = 0; i <size; i++) {
        printf("%d\t", arr[i]);
    }
}

int main () {
    // Declare arrays
    int originalArray[] = {1, 2, 3, 4};
    int size = sizeof(originalArray) / sizeof(originalArray[0]);

    printf("===Original Array===\n");
    printArray(originalArray, size);

    reverseArray(&originalArray[0], &originalArray[size - 1]);

    printf("\n===Reversed Array===\n");
    printArray(originalArray, size);


    
}