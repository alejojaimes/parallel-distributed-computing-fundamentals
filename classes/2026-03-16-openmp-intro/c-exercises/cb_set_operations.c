/**
 * Exercise: Union and Intersection of Sets
 * Write a program that computes the union and intersection of two sets of integers.
 * The program should take two arrays as input, representing the sets, and output the
 * union and intersection of these sets. Use functions to modularize your code.
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE_A 9
#define SIZE_B 6

int contains(int *arr, int size, int val) {
    for (int i = 0; i < size; i++)
    {
        if (*(arr + i) ==  val) {
            return 1; 
        }
    }
    return 0;
}

int *union_operation(int *set_a, int size_a, int *set_b, int size_b, int *rsize) {
    // Init dynamic memory
    int *result = (int *) malloc( (size_a + size_b) * sizeof(int));
    *rsize = 0;
    // Check and validate
    for (int i = 0; i < size_a; i++)
    {
        // Check if the value in set dont appear in the other set.
        int element = set_a[i];
        if (!contains(result, *rsize, element))
        {
            *(result + (*rsize)++) = element;
        }
    }

    for (int i = 0; i < size_b; i++)
    {
        // Check if the value in set dont appear in the other set.
        int element = set_b[i];
        if (!contains(result, *rsize, element))
        {
            *(result + (*rsize)++) = element;
        }
    }
    
    return result;
}

int *insersect_operation(int *set_a, int size_a, int *set_b, int size_b, int *rsize) {
    // Init result
    int * result = (int *) malloc ((size_a + size_b) * sizeof(int));
    *rsize = 0;

    for (int i = 0; i < size_a; i++)
    {
        int element = *(set_a + i);
        if (contains(set_b, size_b, element))
        {
            *(result + (*rsize)++) = element;
        }
        
    }

    return result;
}


void print_set(char *title, int *array, int size){
    printf("%s = {", title);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("}\n");
    
}


int main () {
    
    // Initialize statics sets
    int set_a[SIZE_A] = {8, 19, 87, 1, 2, 65, 55, 7, 9};
    int set_b[SIZE_B] = {19, 85, 98, 55, 2, 4};
    int rsize; // result size

    // print set
    print_set("A", set_a, SIZE_A);
    print_set("B", set_b, SIZE_B);

    // compute union operation
    int *set_union = union_operation(set_a, SIZE_A, set_b, SIZE_B, &rsize);
    print_set("AUB", set_union, rsize);
    free(set_union);

    // compute intersection operation
    int *set_intersection = insersect_operation(set_a, SIZE_A, set_b, SIZE_B, &rsize);
    print_set("AnB", set_intersection, rsize);
    free(set_intersection);
    // union
    //int set_union[]

}