/**
 * Author: Alejandro Jaimes
 * Created at: 06/04/2026
 * Brief: Create an exercises that follows this steps
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 15

void populate_array(int *arr_even, int *arr_odd, int *size_even, int *size_odd) {
    
    int min_range = 1;
    int max_range  = 9;
    
    for (int i = 0; i < N; i++)
    {   
        int rand_number = (rand() % max_range) + 1;
        if (rand_number % 2 == 0)
        {
            *(arr_even + (*size_even)++) = rand_number;
        } else {
            *(arr_odd + (*size_odd)++) = rand_number;
        }
        
    }
    
}

void print_array(int *array, int size) {
    printf("[");
    for (int i = 0; i < size; i++)
    {
        if (i == size -1)  break;
        
        printf("%d, ", *(array + i));
    }
    printf("%d]\n", *(array + size -1));
}

int main() {

    // Declare 2 arrays with dynamic memory
    int *arr_even = (int *) malloc (N *  sizeof(int));
    int *arr_odd =  (int *) malloc (N *  sizeof(int));
    int size_even = 0;
    int size_odd = 0;

    // declare seed
    srand(time(NULL));

    // populate arrays
    populate_array(arr_even, arr_odd, &size_even, &size_odd);

    // print array
    print_array(arr_even, size_even);
    printf("\n");
    print_array(arr_odd, size_odd);






    return 0;
}