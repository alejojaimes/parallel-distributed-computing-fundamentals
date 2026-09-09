#include <stdio.h>
#include <omp.h>

int main () {
    //  Show the thread num, related in the process
    int total_threads = omp_get_max_threads();
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Thread ID: %d/%d Say hello :)\n", 
            thread_id, 
            total_threads);
    }
    return 0;
}