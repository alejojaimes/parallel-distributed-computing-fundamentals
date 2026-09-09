#include <stdio.h>
#include <stdlib.h>

/*
Make an algorithm to find
the max and min element.
*/
void findMaxAndMin(int *array, int size, int *max, int *min) {
    *max = *array;
    *min = *array;
    for(int i = 0; i < size; i++) {
        if(*(array + i) > *max) {
            *max = *(array + i);
        }

        if(*(array + i) < *min) {
            *min = *(array + i);
        }
    }
}

void printArray(int *arr, int size) {
    for(int i = 0; i <size; i++) {
        printf("%d\t", arr[i]);
    }
}

int main () {
    // Declare arrays
    int originalArray[] = {10, 5, 8};
    int size = sizeof(originalArray) / sizeof(originalArray[0]);
    int max, min;

    printf("===Original Array===\n");
    printArray(originalArray, size);

    findMaxAndMin(originalArray, size, &max, &min);

    printf("\n===Min and Max Array===\n");
   printf("\nMax: %d, Min: %d\n", max, min);


    
}