/*
file: c3_03_montecarlo.c
author: Juan Alejandro Carrillo Jaimes
description: a little example to hands on in montecarlo
algorithm using find pi value.
created at: 29 September 2025
*/

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

/*
Algorithm

1. Generate N random numbers between [0,1]
2. Count points inside.
3. apply montecarlo equation = 4 * (inside_points / total_points)
*/

#define N 1000000000

int main () 
{
    // 00. generate seed of random numbers
    srand(time(NULL));

    // 01. declare variables
    long pointsInside = 0;

    // 02. Start config with current time
    clock_t startTime = clock();

    // 03. Simulate montecarlo algorithm
    for (long i = 0; i < N; i++)
    {
        // 3.1 Generate coordenates

        // 3.1.1 Generate X
        double x = (double) rand() / RAND_MAX;
        // 3.1.2 Generate X
        double y = (double) rand() / RAND_MAX;
        // 3.1.3 check if the point is inside the circle.
        double distance = (x*x) + (y*y);
        if(distance <= 1.0) {
            // 3.1.4 count points
            pointsInside++;
        }
        
    }
    // 04. End time algorithm
    clock_t endTime = clock();

    // 05. apply equation
    double piEstimate =  4.0 * ((double)pointsInside / N);
    double elapsedTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;

    // 06. Show results
    printf("Inside points in the circle: %ld\n", pointsInside);
    printf("Total points:  %ld\n", N);
    printf("Estimate PI:  %.10f\n", piEstimate);
    printf("Real PI:  %.10f\n", M_PI);
    printf("Elapsed Time:  %.2f\n", elapsedTime);
    return 0;
}


