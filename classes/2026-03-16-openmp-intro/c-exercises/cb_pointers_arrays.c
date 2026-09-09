#include <stdio.h>

void sum_pointers_array(int *arr, int size) {
    for (int i = 0; i < size; i++)
    {
        int element = (*(arr + i) + 1);
        printf("%d\n", element);
    }
    
}

int main() {
    int arr [] = {71, 92, 43, 44, 16};
    int size = sizeof(arr) / sizeof(arr[0]);

    // call function
    sum_pointers_array(arr, size);


    printf("Total Length: %d\n", size);
    return 0;
}