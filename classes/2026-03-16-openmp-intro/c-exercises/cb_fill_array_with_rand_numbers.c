/**
 * Exercise: Fill Array with Random Numbers (1 - 10)
 * Create a program that initializes an array of a specified 
 * size with random numbers between 1 and 10.
 * 
 * Remember
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define START 1
#define END 10

void populate_array(int *array) {
    for (int i = 0; i < N; i++)
    {
        *(array + i) = (rand() % END) + START;
    }
}

void print_array(int *array) {
    printf("[");
    for (int i = 0; i < N; i++)
    {
        if (i == N -1)  break;
        
        printf("%d, ", *(array + i));
    }
    printf("%d]\n", *(array + N -1));
}

int main () {
    // Seed randoom
    srand(time(NULL));
    int array[N];

    // populate array
    populate_array(array);

    // print array
    print_array(array);    

    return 0;
}


