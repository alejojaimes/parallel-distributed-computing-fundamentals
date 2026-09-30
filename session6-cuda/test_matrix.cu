// test_matrices.cu
#include <stdio.h>
#include <cuda_runtime.h>
#include <time.h>

#define SIZE 1024
#define BLOCK_SIZE 16

// Kernel de multiplicación de matrices
__global__ void matMul(float *A, float *B, float *C, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n && col < n) {
        float sum = 0.0f;
        for (int k = 0; k < n; k++) {
            sum += A[row * n + k] * B[k * n + col];
        }
        C[row * n + col] = sum;
    }
}

// Multiplicación en CPU para comparar
void matMulCPU(float *A, float *B, float *C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            float sum = 0.0f;
            for (int k = 0; k < n; k++)
                sum += A[i * n + k] * B[k * n + j];
            C[i * n + j] = sum;
        }
}

int main() {
    int n = SIZE;
    size_t bytes = n * n * sizeof(float);

    printf("==================================================\n");
    printf("      CUDA Matrix Multiplication %dx%d\n", n, n);
    printf("==================================================\n\n");

    // Alojar memoria en host
    float *h_A = (float*)malloc(bytes);
    float *h_B = (float*)malloc(bytes);
    float *h_C_cpu = (float*)malloc(bytes);
    float *h_C_gpu = (float*)malloc(bytes);

    // Inicializar matrices con valores aleatorios
    for (int i = 0; i < n * n; i++) {
        h_A[i] = (float)rand() / RAND_MAX;
        h_B[i] = (float)rand() / RAND_MAX;
    }

    // ---- CPU ----
    printf("[CPU]\n");
    clock_t cpu_start = clock();
    matMulCPU(h_A, h_B, h_C_cpu, n);
    clock_t cpu_end = clock();
    double cpu_time = (double)(cpu_end - cpu_start) / CLOCKS_PER_SEC;
    printf("  Tiempo: %.4f segundos\n\n", cpu_time);

    // ---- GPU ----
    printf("[GPU]\n");

    // Alojar memoria en device
    float *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);

    // Copiar datos al device
    cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);

    // Configurar grid y bloques
    dim3 block(BLOCK_SIZE, BLOCK_SIZE);
    dim3 grid((n + BLOCK_SIZE - 1) / BLOCK_SIZE, (n + BLOCK_SIZE - 1) / BLOCK_SIZE);

    // Eventos CUDA para medir tiempo
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    matMul<<<grid, block>>>(d_A, d_B, d_C, n);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float gpu_ms = 0;
    cudaEventElapsedTime(&gpu_ms, start, stop);
    printf("  Tiempo: %.4f segundos\n\n", gpu_ms / 1000.0f);

    // Copiar resultado al host
    cudaMemcpy(h_C_gpu, d_C, bytes, cudaMemcpyDeviceToHost);

    // Speedup
    double speedup = cpu_time / (gpu_ms / 1000.0f);
    printf("==================================================\n");
    printf("  Aceleracion GPU vs CPU: %.2fx mas rapido\n", speedup);
    printf("==================================================\n");

    // Liberar memoria
    free(h_A); free(h_B); free(h_C_cpu); free(h_C_gpu);
    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    return 0;
}
