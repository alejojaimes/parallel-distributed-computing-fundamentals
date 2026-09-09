# Classes — registro por fecha

Una carpeta por sesión presencial, nombrada `YYYY-MM-DD-tema`. Es el trabajo tal
cual salió de cada clase (borradores incluidos). La versión pulida y ordenada por
tema está en [`../sessions/`](../sessions/).

| Fecha | Carpeta | Qué se hizo |
|-------|---------|-------------|
| 2026-03-16 | [`2026-03-16-openmp-intro/`](2026-03-16-openmp-intro/) | Ejercicios de C (`c-exercises/`: punteros, conjuntos, primos, matrices) y primeros programas OpenMP (`openmp/`) |
| 2026-03-18 | [`2026-03-18-array-sum/`](2026-03-18-array-sum/) | Suma de un arreglo: `cb_array_sum.c` (secuencial) vs `omp_array_sum.c` (OpenMP) |
| 2026-04-06 | [`2026-04-06-even-odd-split/`](2026-04-06-even-odd-split/) | Separar un arreglo aleatorio en pares e impares con aritmética de punteros |
| 2026-09-07 | [`2026-09-07-calculator/`](2026-09-07-calculator/) | Calculadora básica con selección de operación por carácter |

## Estado de los ejercicios

Todos los ejercicios de C y OpenMP compilan y ejecutan. Los dos ejercicios de
OpenMP de la clase del 16-03 incluyen comentarios que responden a la pregunta
planteada en su cabecera:

- `omp_array_init_by_thread_range.c` — muestra qué posiciones quedan sin
  inicializar cuando `N % NTHREADS != 0`.
- `omp_matrix_row_sum.c` — compara la versión secuencial y la paralela; la suma
  de filas está limitada por el ancho de banda de memoria, así que el speedup
  queda por debajo del número de hilos.
