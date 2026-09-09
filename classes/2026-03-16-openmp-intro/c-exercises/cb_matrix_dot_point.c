/**
 * Exercise: Matrix Dot Product with a Point
 * Write a program that computes the dot product of a matrix and a point (vector).
 * The program should take a matrix and a point as input, and output the resulting vector.
 * Use functions to modularize your code.
 */

#include <stdio.h>
#include <stdlib.h>

#define N 2

void fill_matrix(int **matrix, int size, char variation) {
    int element;
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *) malloc (N * sizeof(int));
        for (int j = 0; j < size; j++)
        {
            if (variation == '1')
            {
                element = (j + N) - (i + 1);
            } else {
                element = i * N + j + 1;
            }
            
            matrix[i][j] = element;
        }
        
    }
    
}

int **dot_point_matrix(int **matrix_a, int **matrix_b, int size) {
    int **dot_matrix = (int **) malloc( N * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        dot_matrix[i] = (int *) malloc (N * sizeof(int));
        for (int j = 0; j < size; j++)
        {
            dot_matrix[i][j] = 0;
            for (int k = 0; k < size; k++)
            {
                dot_matrix[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
            
        }
        
    }
    return dot_matrix;
}


void print_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {   
            printf("%4d, ", matrix[i][j]);
        }        
        printf("\n");
    }
    
}

void free_matrix_memory(int **matrix, int size) {
    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int main () {

    // Init matrix
    int **matrix_a = (int **) malloc( N * sizeof(int *));
    int **matrix_b = (int **) malloc( N * sizeof(int *));
    int **dot_product_matrix;
    
    // Fill matrix a with variation 1
    fill_matrix(matrix_a, N, '1');
    // Fill matrix without variation
    fill_matrix(matrix_b, N, '0');

    // print matrix
    printf("===========MATRIX A ===============\n");
    print_matrix(matrix_a, N);

    printf("===========MATRIX B ===============\n");
    print_matrix(matrix_b, N);

    //Dot product
    dot_product_matrix = dot_point_matrix(matrix_a, matrix_b, N);
    printf("===========DOT PRODUCT MATRIX ===============\n");
    print_matrix(dot_product_matrix, N);


    // Free Memory
    free_matrix_memory(matrix_a, N);
    free_matrix_memory(matrix_b, N);
    free_matrix_memory(dot_product_matrix, N);
    
    return 0;
}