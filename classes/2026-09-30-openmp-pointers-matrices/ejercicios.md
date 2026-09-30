# 5 ejercicios de OpenMP con punteros y matrices

**Directivas permitidas:** `omp parallel`, `omp parallel for`, `schedule(static)`, `reduction`, `critical`, `private`.

**Regla de punteros:** toda matriz es un bloque contiguo creado con `malloc` y se accede solo con aritmética de punteros:

```c
*(matrix + i * cols + j)          // element (i, j)
double *row = matrix + i * cols;  // pointer to row i
```

En cada plantilla, `main` ya está completo. Tú completas las funciones marcadas con `TODO`.

---

## Ejercicio 1 — Promedio de notas

**Archivo:** `omp_01_grade_average.c`

**Problema:** Un curso tiene 10 estudiantes y 6 asignaturas. Hay que calcular el promedio de cada estudiante y saber quién aprueba (promedio ≥ 3.0).

**Directivas:** `omp parallel`, `omp parallel for`, `schedule(static)`.

**Datos:** matriz `grades` de `10 x 6` con `grade(i, j) = 1.0 + ((i*7 + j*3) % 41) / 10.0`

**Qué debes hacer:**

1. `print_team_info`: abrir una región `omp parallel` donde cada hilo imprima su número y el total de hilos.
2. `compute_averages`: repartir los **estudiantes** entre hilos con `parallel for`. Cada hilo suma la fila del estudiante usando un puntero a la fila.

### Plantilla

```c
/**
 * @file omp_01_grade_average.c
 * @brief Computes the average grade of each student in parallel using OpenMP
 * @author Alejandro Jaimes
 * @date 2026-09-30
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define STUDENTS 10
#define SUBJECTS 6
#define PASSING_GRADE 3.0

void print_team_info(void) {
    // TODO: #pragma omp parallel
    {
        // TODO: get the thread id and the total number of threads
        // TODO: printf("Thread %d of %d ready\n", ...);
    }
}

void fill_grades(double *grades, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(grades + i * cols + j) = 1.0 + ((i * 7 + j * 3) % 41) / 10.0;
        }
    }
}

void compute_averages(double *grades, double *averages, int rows, int cols) {
    // TODO: #pragma omp parallel for schedule(static)
    for (int i = 0; i < rows; i++) {
        double *row = /* TODO: pointer to row i */;
        double sum = 0.0;
        // TODO: add the cols grades of the row using *(row + j)
        *(averages + i) = sum / cols;
        printf("Thread %d computed student %d\n", omp_get_thread_num(), i);
    }
}

void print_report(double *grades, double *averages, int rows, int cols) {
    int passed = 0;
    for (int i = 0; i < rows; i++) {
        printf("S%d:", i);
        for (int j = 0; j < cols; j++) {
            printf(" %.1f", *(grades + i * cols + j));
        }
        double avg = *(averages + i);
        printf(" -> %.2f %s\n", avg, avg >= PASSING_GRADE ? "PASS" : "FAIL");
        if (avg >= PASSING_GRADE) passed++;
    }
    printf("Passed: %d of %d\n", passed, rows);
}

int main() {
    // 1. Create matrices with dynamic memory
    double *grades = (double *) malloc(STUDENTS * SUBJECTS * sizeof(double));
    double *averages = (double *) malloc(STUDENTS * sizeof(double));
    // 2. Check if the pointers are not null
    if (grades == NULL || averages == NULL) {
        printf("Not enough memory\n");
        return 1;
    }
    // 3. Show the thread team
    omp_set_num_threads(4);
    print_team_info();
    // 4. Fill grades and compute averages
    fill_grades(grades, STUDENTS, SUBJECTS);
    compute_averages(grades, averages, STUDENTS, SUBJECTS);
    // 5. Print results
    print_report(grades, averages, STUDENTS, SUBJECTS);
    // 6. Free memory
    free(grades);
    free(averages);
    return 0;
}
```

### Salida esperada

Las líneas de los hilos salen en **orden variable**. Con 4 hilos y `static`, el hilo 0 hace los estudiantes 0–2, el 1 hace 3–5, el 2 hace 6–7 y el 3 hace 8–9.

```
Thread 2 of 4 ready
Thread 0 of 4 ready
...
Thread 1 computed student 3
Thread 0 computed student 0
...
S0: 1.0 1.3 1.6 1.9 2.2 2.5 -> 1.75 FAIL
S1: 1.7 2.0 2.3 2.6 2.9 3.2 -> 2.45 FAIL
S2: 2.4 2.7 3.0 3.3 3.6 3.9 -> 3.15 PASS
S3: 3.1 3.4 3.7 4.0 4.3 4.6 -> 3.85 PASS
S4: 3.8 4.1 4.4 4.7 5.0 1.2 -> 3.87 PASS
S5: 4.5 4.8 1.0 1.3 1.6 1.9 -> 2.52 FAIL
S6: 1.1 1.4 1.7 2.0 2.3 2.6 -> 1.85 FAIL
S7: 1.8 2.1 2.4 2.7 3.0 3.3 -> 2.55 FAIL
S8: 2.5 2.8 3.1 3.4 3.7 4.0 -> 3.25 PASS
S9: 3.2 3.5 3.8 4.1 4.4 4.7 -> 3.95 PASS
Passed: 5 of 10
```

---

## Ejercicio 2 — Imagen 4K a escala de grises

**Archivo:** `omp_02_image_grayscale.c`

**Problema:** Convertir una imagen a color de `2160 x 3840` (4K) a escala de grises, calcular su brillo medio y cuántos píxeles son oscuros. Se compara la versión secuencial con la paralela.

**Directivas:** `omp parallel for`, `reduction(+)`, `schedule(static)`.

**Datos:** cada píxel ocupa 3 bytes seguidos (R, G, B). El píxel número `k` empieza en `image + k * 3`.

```
R = (i + j) % 256      G = (2 * i) % 256      B = (3 * j) % 256
gray = 0.299 R + 0.587 G + 0.114 B   (redondeado)
dark pixel: gray < 50
```

**Qué debes hacer:**

1. `to_gray`: calcular el gris de un píxel usando `*(pixel + 0)`, `*(pixel + 1)`, `*(pixel + 2)`.
2. `grayscale_parallel`: copiar la versión secuencial y paralelizarla. `brightness` y `dark` se acumulan con `reduction`.

### Plantilla

```c
/**
 * @file omp_02_image_grayscale.c
 * @brief Converts a 4K RGB image to grayscale and computes its brightness using OpenMP
 * @author Alejandro Jaimes
 * @date 2026-09-30
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define HEIGHT 2160
#define WIDTH 3840
#define DARK_LIMIT 50

void fill_image(unsigned char *image, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char *pixel = image + ((long) i * width + j) * 3;
            *(pixel + 0) = (i + j) % 256;   // R
            *(pixel + 1) = (2 * i) % 256;   // G
            *(pixel + 2) = (3 * j) % 256;   // B
        }
    }
}

int to_gray(unsigned char *pixel) {
    // TODO: return (int) (0.299 * R + 0.587 * G + 0.114 * B + 0.5);
}

long long grayscale_sequential(unsigned char *image, unsigned char *gray,
                               long total_pixels, long *dark_pixels) {
    long long brightness = 0;
    long dark = 0;
    for (long k = 0; k < total_pixels; k++) {
        int value = to_gray(image + k * 3);
        *(gray + k) = (unsigned char) value;
        brightness += value;
        if (value < DARK_LIMIT) dark++;
    }
    *dark_pixels = dark;
    return brightness;
}

long long grayscale_parallel(unsigned char *image, unsigned char *gray,
                             long total_pixels, long *dark_pixels) {
    long long brightness = 0;
    long dark = 0;
    // TODO: #pragma omp parallel for reduction(...) schedule(static)
    // TODO: same loop as the sequential version
    *dark_pixels = dark;
    return brightness;
}

int main() {
    // 1. Create images with dynamic memory
    long total_pixels = (long) HEIGHT * WIDTH;
    unsigned char *image = (unsigned char *) malloc(total_pixels * 3);
    unsigned char *gray = (unsigned char *) malloc(total_pixels);
    // 2. Check if the pointers are not null
    if (image == NULL || gray == NULL) {
        printf("Not enough memory\n");
        return 1;
    }
    // 3. Fill the color image
    fill_image(image, HEIGHT, WIDTH);
    // 4. Sequential version
    long dark_seq;
    double start_time = omp_get_wtime();
    long long brightness_seq = grayscale_sequential(image, gray, total_pixels, &dark_seq);
    double time_seq = omp_get_wtime() - start_time;
    // 5. Parallel version
    long dark_par;
    start_time = omp_get_wtime();
    long long brightness_par = grayscale_parallel(image, gray, total_pixels, &dark_par);
    double time_par = omp_get_wtime() - start_time;
    // 6. Print results
    printf("Average brightness: %.2f (sequential) | %.2f (parallel)\n",
           (double) brightness_seq / total_pixels, (double) brightness_par / total_pixels);
    printf("Dark pixels: %ld (%.2f%%)\n", dark_par, 100.0 * dark_par / total_pixels);
    printf("gray(0,0)=%d gray(100,200)=%d gray(2159,3839)=%d\n",
           *gray, *(gray + 100 * WIDTH + 200), *(gray + (long) 2159 * WIDTH + 3839));
    printf("Sequential time: %.3fs\n", time_seq);
    printf("Parallel time: %.3fs\n", time_par);
    printf("Speedup: %.2f\n", time_seq / time_par);
    // 7. Free memory
    free(image);
    free(gray);
    return 0;
}
```

### Salida esperada

```
Average brightness: 126.72 (sequential) | 126.72 (parallel)
Dark pixels: 487185 (5.87%)
gray(0,0)=0 gray(100,200)=141 gray(2159,3839)=192
Sequential time: 0.0xxs      <- variable
Parallel time: 0.0xxs        <- variable
Speedup: x.xx                <- variable
```

Si quitas la `reduction`, el brillo paralelo saldrá distinto del secuencial y cambiará en cada ejecución.

---

## Ejercicio 3 — Temperaturas extremas

**Archivo:** `omp_03_temperature_extremes.c`

**Problema:** 12 estaciones meteorológicas registran una temperatura diaria durante un año. Se quiere la temperatura máxima, la mínima y la media de toda la red, y además **en qué estación y qué día** ocurrieron la máxima y la mínima.

**Directivas:** `reduction(max)`, `reduction(min)`, `reduction(+)`, `critical`.

**Datos:** matriz `temps` de `12 x 365`:

```
temp(s, d) = 18.0 + 8.0 * sin(2π d / 365) + 0.5 s - 0.3 ((s * d) % 7)
```

**Qué debes hacer:**

1. `network_summary`: recorrer toda la matriz como un vector y obtener máximo, mínimo y suma con tres `reduction`.
2. `find_extremes`: la `reduction` solo da el valor, no la posición. Reparte las **estaciones** entre hilos; cada iteración busca el máximo y mínimo de su estación en un `Record` local y al final lo compara con el global dentro de un `critical`.

### Plantilla

```c
/**
 * @file omp_03_temperature_extremes.c
 * @brief Finds the temperature extremes of a weather station network using OpenMP
 * @author Alejandro Jaimes
 * @date 2026-09-30
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <omp.h>

#define STATIONS 12
#define DAYS 365

typedef struct {
    double value;
    int station;
    int day;
} Record;

void fill_temperatures(double *temps, int stations, int days) {
    for (int s = 0; s < stations; s++) {
        for (int d = 0; d < days; d++) {
            *(temps + s * days + d) = 18.0 + 8.0 * sin(2 * M_PI * d / 365.0)
                                      + 0.5 * s - 0.3 * ((s * d) % 7);
        }
    }
}

void network_summary(double *temps, int total, double *max_temp,
                     double *min_temp, double *mean_temp) {
    double max_value = -DBL_MAX;
    double min_value = DBL_MAX;
    double sum = 0.0;
    // TODO: #pragma omp parallel for reduction(max:...) reduction(min:...) reduction(+:...)
    for (int k = 0; k < total; k++) {
        double t = *(temps + k);
        // TODO: update max_value, min_value and sum
    }
    *max_temp = max_value;
    *min_temp = min_value;
    *mean_temp = sum / total;
}

void find_extremes(double *temps, int stations, int days,
                   Record *hottest, Record *coldest) {
    hottest->value = -DBL_MAX;
    coldest->value = DBL_MAX;
    // TODO: #pragma omp parallel for schedule(static)
    for (int s = 0; s < stations; s++) {
        double *row = /* TODO: pointer to station s */;
        Record local_max = {-DBL_MAX, s, -1};
        Record local_min = {DBL_MAX, s, -1};
        for (int d = 0; d < days; d++) {
            // TODO: update local_max and local_min (value and day)
        }
        // TODO: #pragma omp critical
        {
            // TODO: if local_max is greater than *hottest, replace it
            // TODO: if local_min is lower than *coldest, replace it
        }
    }
}

int main() {
    // 1. Create matrix with dynamic memory
    double *temps = (double *) malloc(STATIONS * DAYS * sizeof(double));
    // 2. Check if the pointer is not null
    if (temps == NULL) {
        printf("Not enough memory\n");
        return 1;
    }
    // 3. Fill temperatures
    fill_temperatures(temps, STATIONS, DAYS);
    // 4. Network summary
    double max_temp, min_temp, mean_temp;
    network_summary(temps, STATIONS * DAYS, &max_temp, &min_temp, &mean_temp);
    // 5. Location of the extremes
    Record hottest, coldest;
    find_extremes(temps, STATIONS, DAYS, &hottest, &coldest);
    // 6. Print results
    printf("Max: %.3f  Min: %.3f  Mean: %.3f\n", max_temp, min_temp, mean_temp);
    printf("Hottest: %.3f at station %d, day %d\n", hottest.value, hottest.station, hottest.day);
    printf("Coldest: %.3f at station %d, day %d\n", coldest.value, coldest.station, coldest.day);
    // 7. Free memory
    free(temps);
    return 0;
}
```

### Salida esperada

```
Max: 31.500  Min: 8.704  Mean: 20.002
Hottest: 31.500 at station 11, day 91
Coldest: 8.704 at station 1, day 272
```

**Pregunta:** ¿por qué el `critical` se pone al final de cada estación y no dentro del bucle de días?

---

## Ejercicio 4 — Rutas aéreas con una escala

**Archivo:** `omp_04_flight_routes.c`

**Problema:** Seis ciudades están conectadas por vuelos directos. Si `A` es la matriz de vuelos directos (1 = hay vuelo), el producto `A · A` dice **cuántas rutas con una escala** hay entre cada par de ciudades. Además se quiere el total de esas rutas y la ciudad que mejor funciona como hub (la que llega a más destinos con máximo una escala).

**Directivas:** `omp parallel for`, `private`, `reduction(+)`, `critical`.

**Datos:**

```
        BOG MDE CLO CTG BGA CUC
BOG      0   1   1   0   1   0
MDE      1   0   1   1   0   0
CLO      1   1   0   1   0   0
CTG      0   1   1   0   0   0
BGA      1   0   0   0   0   1
CUC      0   0   0   0   1   0
```

**Qué debes hacer:**

1. `multiply_matrices`: producto de matrices. `j`, `k` y `acc` se declaran fuera, así que van en `private`.
2. `count_routes`: sumar las rutas entre ciudades distintas (`i != j`) con `reduction`.
3. `find_best_hub`: cada ciudad cuenta sus destinos alcanzables (`direct(i,j) > 0` o `routes(i,j) > 0`, con `i != j`) y actualiza el mejor dentro de un `critical`.

### Plantilla

```c
/**
 * @file omp_04_flight_routes.c
 * @brief Counts one-stop flight routes between cities with a parallel matrix product
 * @author Alejandro Jaimes
 * @date 2026-09-30
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define CITIES 6

void multiply_matrices(int *a, int *b, int *result, int n) {
    int j, k, acc;
    // TODO: #pragma omp parallel for private(...) schedule(static)
    for (int i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            acc = 0;
            // TODO: acc += a(i, k) * b(k, j) using pointer arithmetic
            *(result + i * n + j) = acc;
        }
    }
}

int count_routes(int *routes, int n) {
    int total = 0;
    int j;
    // TODO: #pragma omp parallel for private(...) reduction(...)
    for (int i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            // TODO: add routes(i, j) only when i != j
        }
    }
    return total;
}

int find_best_hub(int *direct, int *routes, int n, int *best_reach) {
    int hub = -1;
    *best_reach = -1;
    // TODO: #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; i++) {
        int reach = 0;
        // TODO: count destinations j != i with direct(i, j) > 0 or routes(i, j) > 0
        // TODO: #pragma omp critical
        {
            // TODO: if reach > *best_reach, update *best_reach and hub
        }
    }
    return hub;
}

void print_matrix(int *matrix, const char **names, int n) {
    printf("     ");
    for (int j = 0; j < n; j++) printf("%5s", names[j]);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%s  ", names[i]);
        for (int j = 0; j < n; j++) printf("%5d", *(matrix + i * n + j));
        printf("\n");
    }
}

int main() {
    const char *names[CITIES] = {"BOG", "MDE", "CLO", "CTG", "BGA", "CUC"};
    int data[CITIES * CITIES] = {0, 1, 1, 0, 1, 0,
                                 1, 0, 1, 1, 0, 0,
                                 1, 1, 0, 1, 0, 0,
                                 0, 1, 1, 0, 0, 0,
                                 1, 0, 0, 0, 0, 1,
                                 0, 0, 0, 0, 1, 0};
    // 1. Create matrices with dynamic memory
    int *direct = (int *) malloc(CITIES * CITIES * sizeof(int));
    int *routes = (int *) malloc(CITIES * CITIES * sizeof(int));
    // 2. Check if the pointers are not null
    if (direct == NULL || routes == NULL) {
        printf("Not enough memory\n");
        return 1;
    }
    // 3. Copy the direct flights
    for (int k = 0; k < CITIES * CITIES; k++) *(direct + k) = *(data + k);
    // 4. One-stop routes = direct * direct
    multiply_matrices(direct, direct, routes, CITIES);
    // 5. Total routes and best hub
    int total = count_routes(routes, CITIES);
    int best_reach;
    int hub = find_best_hub(direct, routes, CITIES, &best_reach);
    // 6. Print results
    printf("One-stop routes:\n");
    print_matrix(routes, names, CITIES);
    printf("Total one-stop routes: %d\n", total);
    printf("Best hub: %s (%d destinations)\n", names[hub], best_reach);
    // 7. Free memory
    free(direct);
    free(routes);
    return 0;
}
```

### Salida esperada

```
One-stop routes:
       BOG  MDE  CLO  CTG  BGA  CUC
BOG      3    1    1    2    0    1
MDE      1    3    2    1    1    0
CLO      1    2    3    1    1    0
CTG      2    1    1    2    0    0
BGA      0    1    1    0    2    0
CUC      1    0    0    0    0    1
Total one-stop routes: 22
Best hub: BOG (5 destinations)
```

Por ejemplo, de BOG a CTG hay 2 rutas con una escala: por MDE y por CLO.

---

## Ejercicio 5 — Calor en una placa metálica

**Archivo:** `omp_05_heat_diffusion.c`

**Problema:** Una placa cuadrada tiene su borde superior a 100 °C y los otros tres a 0 °C. Se quiere la temperatura de equilibrio de cada punto. Con el método de Jacobi, cada punto interior se reemplaza por el promedio de sus 4 vecinos, y se repite hasta que el mayor cambio de una iteración sea ≤ `1e-4`.

**Directivas:** `omp parallel for`, `private`, `reduction(max)`, `schedule(static)`.

**Datos:** malla de `128 x 128`. Con `p = current + i*n + j`, los vecinos son:

```
arriba: *(p - n)    abajo: *(p + n)    izquierda: *(p - 1)    derecha: *(p + 1)
```

**Qué debes hacer:**

1. `jacobi_step`: recorrer los puntos interiores en paralelo, escribir el nuevo valor en `next` y devolver el mayor cambio con `reduction(max:...)`.
2. `solve_plate`: repetir `jacobi_step` e **intercambiar los punteros** `current` y `next` en cada iteración (se reciben como `double **` para que el intercambio se vea en `main`).

Las iteraciones son secuenciales (cada una depende de la anterior); lo que se paraleliza es el recorrido de la malla.

### Plantilla

```c
/**
 * @file omp_05_heat_diffusion.c
 * @brief Solves the steady-state heat distribution of a plate with the Jacobi method using OpenMP
 * @author Alejandro Jaimes
 * @date 2026-09-30
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define SIZE 128
#define TOLERANCE 1e-4
#define MAX_ITER 20000

void init_plate(double *plate, int n) {
    for (int k = 0; k < n * n; k++) *(plate + k) = 0.0;
    for (int j = 0; j < n; j++) *(plate + j) = 100.0;   // top edge
}

double jacobi_step(double *current, double *next, int n) {
    double max_change = 0.0;
    int j;
    // TODO: #pragma omp parallel for private(...) reduction(max:...) schedule(static)
    for (int i = 1; i < n - 1; i++) {
        for (j = 1; j < n - 1; j++) {
            double *p = /* TODO: pointer to point (i, j) */;
            double value = /* TODO: 0.25 * (sum of the 4 neighbors) */;
            double change = fabs(value - *p);
            // TODO: update max_change
            *(next + i * n + j) = value;
        }
    }
    return max_change;
}

int solve_plate(double **current, double **next, int n, double *final_change) {
    int iter = 0;
    double change = 1.0;
    while (change > TOLERANCE && iter < MAX_ITER) {
        change = jacobi_step(*current, *next, n);
        // TODO: swap *current and *next
        iter++;
    }
    *final_change = change;
    return iter;
}

int main() {
    int threads[] = {1, 2, 4};
    double time_one_thread = 0.0;
    for (int t = 0; t < 3; t++) {
        // 1. Create plates with dynamic memory
        double *current = (double *) malloc(SIZE * SIZE * sizeof(double));
        double *next = (double *) malloc(SIZE * SIZE * sizeof(double));
        // 2. Check if the pointers are not null
        if (current == NULL || next == NULL) {
            printf("Not enough memory\n");
            return 1;
        }
        // 3. Initial conditions
        init_plate(current, SIZE);
        init_plate(next, SIZE);
        // 4. Solve with t threads
        omp_set_num_threads(threads[t]);
        double final_change;
        double start_time = omp_get_wtime();
        int iter = solve_plate(&current, &next, SIZE, &final_change);
        double elapsed_time = omp_get_wtime() - start_time;
        if (t == 0) time_one_thread = elapsed_time;
        // 5. Print results
        printf("Threads=%d iter=%d change=%.6f center=%.4f near_top=%.4f time=%.3fs speedup=%.2f\n",
               threads[t], iter, final_change,
               *(current + (SIZE / 2) * SIZE + SIZE / 2),
               *(current + 1 * SIZE + SIZE / 2),
               elapsed_time, time_one_thread / elapsed_time);
        // 6. Free memory
        free(current);
        free(next);
    }
    return 0;
}
```

### Salida esperada

```
Threads=1 iter=15754 change=0.000100 center=24.3448 near_top=98.4052 time=x.xxxs speedup=1.00
Threads=2 iter=15754 change=0.000100 center=24.3448 near_top=98.4052 time=x.xxxs speedup=x.xx
Threads=4 iter=15754 change=0.000100 center=24.3448 near_top=98.4052 time=x.xxxs speedup=x.xx
```

Los números (`iter`, `center`, `near_top`) deben ser **idénticos** con cualquier cantidad de hilos. Si cambian, hay una condición de carrera (por ejemplo, olvidar `j` en `private`).
