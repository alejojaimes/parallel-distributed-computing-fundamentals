/*
 ============================================================================
 Archivo        : mpi_01_array_sum.c
 Autor          : Prf. Juan Alejandro Carrillo Jaimes
 Descripción    : Calcular la suma de un arreglo grande distribuyéndolo
                  entre varios procesos con MPI.
 
 Conceptos clave:
   - Distribución de datos con MPI_Scatter.
   - Cálculo local de sumas parciales en cada proceso.
   - Recolección de resultados con MPI_Reduce.
 
 Compilación:
   mpicc mpi_01_array_sum.c -o mpi_01_array_sum

 Ejecución (ejemplo con 4 procesos):
   mpirun -np 4 ./mpi_01_array_sum
 ============================================================================
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000

// Función que inicializa los datos en el proceso 0
int* initialize_data(int rank) {
    int *data = NULL;
    if (rank == 0) {
        data = (int*) malloc(N * sizeof(int));
        
        for (int i = 0; i < N; i++) {
            data[i] = ((i + 1) * 5) % 100;
        }
        printf("Proceso 0 inicializando array de %d de datos\n", N);
    }
    return data;
}

// Función que reparte datos con Scatter
int* distribute_data(int *data, int local_n, int rank, int size) {
    int *local_data = (int*) malloc(local_n * sizeof(int));
    MPI_Scatter(data, local_n, MPI_INT,
                local_data, local_n, MPI_INT,
                0, MPI_COMM_WORLD);
    return local_data;
}

// Función que calcula suma local
long long compute_local_sum(int *local_data, int local_n, int rank) {
    long long local_sum = 0;
    for (int i = 0; i < local_n; i++) {
        local_sum += local_data[i];
    }
    printf("Proceso %d recibio %d elementos. Suma parcial = %lld\n",
           rank, local_n, local_sum);
    return local_sum;
}

// Función que reduce todas las sumas locales al proceso 0
long long collect_global_sum(long long local_sum) {
    long long total_sum = 0;
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    return total_sum;
}

int main(int argc, char** argv) {
    int rank, size;
    int *data = NULL, *local_data;
    long long local_sum, total_sum;
    int local_n;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_n = N / size;
    data = initialize_data(rank);
    local_data = distribute_data(data, local_n, rank, size);
    local_sum = compute_local_sum(local_data, local_n, rank);
    total_sum = collect_global_sum(local_sum);

    if (rank == 0) {
        printf("Suma total del arreglo de %d elementos = %lld\n", N, total_sum);
        free(data);
    }

    free(local_data);
    MPI_Finalize();
    return 0;
}