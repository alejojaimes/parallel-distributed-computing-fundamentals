#include <stdio.h>
#include <time.h>
#include <omp.h>                         // FIX 1: < >
#define N 2000000                         // FIX 2: N correcto


void fill_array(int *array) {
    for (int i = 0; i < N; i++) {
        *(array + i) = N + i + 1;
    }
}
long long sum_sequential(int *array) {
    long long sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += *(array + i);
    }
    return sum;
}

int main() {
    int total_threads = omp_get_max_threads();
    int array[N];
    fill_array(array);

    clock_t time_seq_start = clock();

    long long total_sum_seq = sum_sequential(array);

    clock_t time_seq_end = clock();


    long long partial_sums[total_threads]; // FIX 3: long long

    double start_time = omp_get_wtime();
    #pragma omp parallel
    {
        int thread_id  = omp_get_thread_num();
        int chunk_size = N / total_threads;
        int start      = thread_id * chunk_size;
        int end        = (thread_id == total_threads - 1)
                         ? N : start + chunk_size;

        long long local_sum = 0;
        for (int i = start; i < end; i++) {
            local_sum += *(array + i);
        }

        partial_sums[thread_id] = local_sum; // FIX 4: mismo tipo
        printf("Thread %d/%d -> range [%d, %d), sum = %lld\n",
               thread_id, total_threads, start, end, local_sum);
    }
    double end_time = omp_get_wtime();

    long long total_sum = 0;
    for (int i = 0; i < total_threads; i++) {
        total_sum += *(partial_sums + i);
    }

    printf("\nTotal Parallel= %lld\n", total_sum);
    printf("\nTotal Sequential= %lld\n", total_sum_seq);
    printf("\nTime Sequential = %.3f\n", ((double)(time_seq_end- time_seq_start) / CLOCKS_PER_SEC));
    printf("\nTime Parallel = %.3f\n", ((end_time - start_time)));

    return 0;
}