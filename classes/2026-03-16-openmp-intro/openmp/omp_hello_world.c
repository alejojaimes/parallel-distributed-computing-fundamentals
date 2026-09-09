/**
 * Exercise 1: Hello World with OpenMP
 * Brief: Verify that OpenMP is properly installed and configured 
 * by writing a simple "Hello, World!" program 
 * that utilizes OpenMP to print messages from multiple threads.
 * 
*/

#include <stdio.h>
#include <omp.h>

int main () {

    #pragma omp parallel 
    {
        printf("Hello world!\n");
    }
    // gcc omp_hello_world.c -o omp_hello_world.exe
    // gcc -fopenmp omp_hello_world.c -o omp_hello_world.exe
    return 0;
}



