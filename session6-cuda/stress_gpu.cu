// stress_gpu.cu
#include <stdio.h>
#include <cuda_runtime.h>

#define SIZE 16384
#define BLOCK_SIZE 32

__global__ void matMulShared(float *A, float *B, float *C, int n) {
    __shared__ float tileA[32][32];
    __shared__ float tileB[32][32];

    int row = blockIdx.y * BLOCK_SIZE + threadIdx.y;
    int col = blockIdx.x * BLOCK_SIZE + threadIdx.x;
    float sum = 0.0f;

    for (int t = 0; t < (n + BLOCK_SIZE - 1) / BLOCK_SIZE; t++) {
        // Cargar tiles en memoria compartida
        if (row < n && t * BLOCK_SIZE + threadIdx.x < n)
            tileA[threadIdx.y][threadIdx.x] = A[row * n + t * BLOCK_SIZE + threadIdx.x];
        else
            tileA[threadIdx.y][threadIdx.x] = 0.0f;

        if (col < n && t * BLOCK_SIZE + threadIdx.y < n)
            tileB[threadIdx.y][threadIdx.x] = B[(t * BLOCK_SIZE + threadIdx.y) * n + col];
        else
            tileB[threadIdx.y][threadIdx.x] = 0.0f;

        __syncthreads();

        for (int k = 0; k < BLOCK_SIZE; k++)
            sum += tileA[threadIdx.y][k] * tileB[k][threadIdx.x];

        __syncthreads();
    }

    if (row < n && col < n)
        C[row * n + col] = sum;
}

void printGPUInfo() {
    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, 0);
    printf("==================================================\n");
    printf("  GPU: %s\n", prop.name);
    printf("  VRAM:          %.0f MB\n", prop.totalGlobalMem / 1024.0 / 1024.0);
    printf("  CUDA Cores:    %d SMs x %d = %d cores\n",
           prop.multiProcessorCount, 128,
           prop.multiProcessorCount * 128);
    printf("  Clock Speed:   %.0f MHz\n", prop.clockRate / 1000.0);
    printf("  Shared Mem/SM: %zu KB\n", prop.sharedMemPerBlock / 1024);
    printf("  Max Threads/Block: %d\n", prop.maxThreadsPerBlock);
    printf("==================================================\n\n");
}

int main() {
    printGPUInfo();

    // Tamaños a probar
    int sizes[] = {1024, 2048, 4096, 8192};
    int num_sizes = 4;

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        size_t bytes = (size_t)n * n * sizeof(float);

        printf("Matriz %dx%d (%.1f MB por matriz)\n", n, n, bytes / 1024.0 / 1024.0);

        // Verificar VRAM disponible
        size_t free_mem, total_mem;
        cudaMemGetInfo(&free_mem, &total_mem);
        if (bytes * 3 > free_mem) {
            printf("  [!] VRAM insuficiente (necesita %.0f MB, disponible %.0f MB)\n\n",
                   bytes * 3.0 / 1024 / 1024, free_mem / 1024.0 / 1024.0);
            continue;
        }

        // Alojar memoria
        float *h_A = (float*)malloc(bytes);
        float *h_B = (float*)malloc(bytes);
        float *d_A, *d_B, *d_C;

        cudaMalloc(&d_A, bytes);
        cudaMalloc(&d_B, bytes);
        cudaMalloc(&d_C, bytes);

        // Inicializar
        for (size_t i = 0; i < (size_t)n * n; i++) {
            h_A[i] = (float)rand() / RAND_MAX;
            h_B[i] = (float)rand() / RAND_MAX;
        }

        cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
        cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);

        dim3 block(BLOCK_SIZE, BLOCK_SIZE);
        dim3 grid((n + BLOCK_SIZE - 1) / BLOCK_SIZE, (n + BLOCK_SIZE - 1) / BLOCK_SIZE);

        // Warmup
        matMulShared<<<grid, block>>>(d_A, d_B, d_C, n);
        cudaDeviceSynchronize();

        // Medir
        cudaEvent_t start, stop;
        cudaEventCreate(&start);
        cudaEventCreate(&stop);

        cudaEventRecord(start);
        matMulShared<<<grid, block>>>(d_A, d_B, d_C, n);
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);

        float ms = 0;
        cudaEventElapsedTime(&ms, start, stop);

        // TFLOPS = 2 * N^3 operaciones
        double tflops = (2.0 * n * n * n) / (ms / 1000.0) / 1e12;

        printf("  Tiempo:  %.4f segundos\n", ms / 1000.0f);
        printf("  TFLOPS:  %.4f\n\n", tflops);

        free(h_A); free(h_B);
        cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
    }

    printf("==================================================\n");
    printf("  Stress test completado\n");
    printf("==================================================\n");

    return 0;
}
