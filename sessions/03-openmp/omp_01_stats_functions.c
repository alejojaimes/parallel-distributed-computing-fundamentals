/*
 ============================================================================
 Archivo        : omp_01_stats_functions.c
 Autor          : Prf. Juan Alejandro Carrillo Jaimes
 Descripción    : Ejemplo de uso de OpenMP en funciones en C.
                  El programa calcula el promedio y la desviación estándar 
                  de un arreglo grande de datos, utilizando regiones paralelas 
                  dentro de funciones.
 
 Conceptos clave:
   - Uso de #pragma omp parallel for con cláusula reduction.
   - Paralelización dentro de funciones auxiliares, no solo en main().
   - Acceso a memoria compartida en un modelo de multiprocesamiento.
   - Buenas prácticas: evitar regiones paralelas demasiado pequeñas.

 Compilación:
   gcc omp_01_stats_functions.c -o omp_01_stats_functions -fopenmp -lm

 Ejecución:
   ./omp_01_stats_functions
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 5

void iniatilizeArray (double *data) {
   for (int i = 0; i <N; i++)
   {
      int fiveMultiples = ((i + 1) * 5) % 100;
      data[i] = (double) fiveMultiples; // multiples of 5
   }
}

double calculateAverage(double *data) {
  double sum = 0.0;
  #pragma omp parallel for reduction(+:sum)
  for (int i = 0; i < N; i++)
  {
    int totalThreads = omp_get_num_threads();
    int threadNum = omp_get_thread_num();
    printf("fx:Average - Working Thread %d of %d \n", threadNum, totalThreads);
    sum += data[i];
  }
  return sum / N;
}

double calculateSD(double *data, double avg) {
   // Calculate Variance
   double variance = 0.0;
   #pragma omp parallel reduction (+:variance)
   for (int i = 0; i < N; i++)
   {
      int totalThreads = omp_get_num_threads();
      int threadNum = omp_get_thread_num();
      printf("fx:Stddev - Working Thread %d of %d \n", threadNum, totalThreads);
      variance += ( (data[i] - avg) * (data[i] - avg));
   }
   variance = variance / N;
   // Calculate standard derivation
   double stddev = sqrt(variance);
   
   return stddev;
}



int main() {
  
    double *data;

    omp_set_num_threads(4);

    // reserve memory for array data
    data = (double *) malloc(N * sizeof(double));

    iniatilizeArray(data);

    // measure time
    double starTime = omp_get_wtime();

    // 01. Calculate parallel sum
    double avg = calculateAverage(data);

    // 02. Calculate parallel varianze
    double stddev = calculateSD(data, avg);

    // end parallel time
    double elapsedTime = omp_get_wtime() - starTime;

    printf("Total Data: %d\nMean: %.2f\nStandard Derivation: %.2f\nElapsed Time: %f sg",N, avg, stddev, elapsedTime);

    free(data);

    return 0;
}