#include <stdio.h>

/*
Sort algoritm using
aritmetich operations
*/

void sortArray(int *pinit, int *pend) {
    while (pinit < pend)
    {
        int tmp = *pinit;
        *pinit = *pend;
        *pend = tmp;

        pinit++;
        pend--;
    }    
}

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++)
    {
        printf("%d\t", arr[i]);
    }
    
}

int main () {
    int array[] = {25, 95, 10, 19, 10, 5, 7};

    int size = sizeof(array) / sizeof(array[0]);

    printf("===Original Array ===");
    printArray(array, size);


    // Sorting array
    sortArray(&array[0], &array[size - 1]);
    printArray(array, size);

}