#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int totalThreads = omp_get_num_threads();
        int threadNum = omp_get_thread_num();
        printf("Thread %d of %d \n", threadNum, totalThreads);
    }
    return 0;
}