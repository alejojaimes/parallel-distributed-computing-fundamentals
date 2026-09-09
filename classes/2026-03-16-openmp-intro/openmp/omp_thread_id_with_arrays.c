/**
 * Ecercise 2: Thread ID with Arrays in OpenMP
 * Brief: Create a program that initializes an array of integers and uses OpenMP t
 * o have multiple threads print their thread ID along with the corresponding array 
 * element they are processing.
 * Question: Is the print order consistent? What happens if you change 
 * opm_set_num_threads() to a different value?
*/

#include <stdio.h>
#include <omp.h>
#define N 10000

void fill_array(int *array) {
    for (int i = 0; i < N; i++)
    {
        *(array + i) = N + i + 1;
    }
    
}

int main () {
    int total_threads = omp_get_max_threads();
    int array [N];
    fill_array(array);

    int partial_sums[total_threads];

    #pragma omp parallel 
    {
        // Get thread
        int thread_id = omp_get_thread_num();
        
        // Calculate range chunk
        int chunk_size = N / total_threads; // 1.250
        int start = thread_id * chunk_size; // pt = 6 | pt * 1.250 => 7500
        int end = (thread_id == total_threads - 1) ? N: start + chunk_size; // 7500 + 1250 => 8750

        // Calculate sum by thread locally
        long long local_sum = 0;
        for (int i = start; i < end; i++)
        {
            local_sum += *(array + i);
        }
        
        // Update partial_sums
        partial_sums[thread_id] = local_sum;
        printf("Thread: %d / %d->\t range[ %d, %d), partial_sum = %lld\n",
                thread_id, total_threads, start, end, local_sum);
    }  
    
    // Reduction for single value, like the sum of the all values
    long long total_sum = 0;
    for (int i = 0; i < total_threads; i++)
    {
        total_sum += *(partial_sums + i);
    }

    printf("\n Total = %lld\n", total_sum);
    
    return 0;
}