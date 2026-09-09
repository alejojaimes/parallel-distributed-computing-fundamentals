/**
 * Exercise 3: Array Initialization by Thread Range
 * Brief: Write a program that initializes an array based on its ID.
 * Introduces manual work partitioning with pointers.
 * Question: What happens is N is not divisible by NTHREADS? Which positions are
 * left uninitialized?
 */

#include <stdio.h>
#include <omp.h>

#define N 12
#define NTHREADS 3