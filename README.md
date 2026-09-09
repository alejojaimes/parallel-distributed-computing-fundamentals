# parallel-distributed-computing-fundamentals

Este repositorio reúne materiales, ejemplos y ejercicios destinados al aprendizaje de los fundamentos de la computación paralela y distribuida. El enfoque es práctico y progresivo, abarcando desde los conceptos básicos del lenguaje C hasta modelos de programación con OpenMP, MPI, CUDA y Spark.

---

## Cómo está organizado el repositorio

El material se organiza en **dos vistas complementarias**:

- **`sessions/`** — currículo ordenado por tema. Cada carpeta agrupa la teoría y los
  ejercicios de un bloque (C básico, OpenMP, MPI, …). Es la ruta recomendada para
  estudiar de cero.
- **`classes/`** — trabajo crudo clase a clase, una carpeta por fecha
  (`YYYY-MM-DD-tema`). Es el registro de lo que se hizo en cada sesión presencial,
  tal cual, sin pulir.

```
parallel-distributed-computing-fundamentals/
│── LICENSE
│── README.md
│── docs/                  # Documentación, guías y material de apoyo
│── sessions/              # Currículo por tema (ver tabla abajo)
│── classes/               # Registro por fecha de cada clase
└── _legacy/               # Material antiguo que ya no se usa (NO versionado)
```

---

## Sessions (currículo por tema)

| # | Carpeta | Tema | Contenido |
|---|---------|------|-----------|
| 1 | [`sessions/01-c-basico/`](sessions/01-c-basico/) | Introducción a C | Hola mundo, capicúa, punteros y memoria |
| 2 | [`sessions/02-c-ejercicios/`](sessions/02-c-ejercicios/) | Ejercicios en C | Lógica, punteros y ejercicios complejos (archivo plano, Montecarlo) |
| 3 | [`sessions/03-openmp/`](sessions/03-openmp/) | Programación paralela con OpenMP | Hilos, `reduction`, primos en paralelo, demo secuencial vs paralelo |
| 4 | [`sessions/04-mpi/`](sessions/04-mpi/) | Programación distribuida con MPI | Test de entorno, suma de arreglo distribuida |
| 5 | [`sessions/05-segmentacion-imagenes/`](sessions/05-segmentacion-imagenes/) | Segmentación de imágenes | Segmentación binaria y RGB en paralelo sobre imágenes PPM |

> **Próximos bloques previstos:** `session6-cuda` (cómputo en GPU) y
> `session7-spark` (procesamiento distribuido de datos). Ver la nomenclatura y los
> comandos de compilación más abajo.

---

## Classes (registro por fecha)

| Fecha | Carpeta | Qué se hizo |
|-------|---------|-------------|
| 2026-03-16 | [`classes/2026-03-16-openmp-intro/`](classes/2026-03-16-openmp-intro/) | Ejercicios de C (punteros, conjuntos, primos, matrices) y primeros programas OpenMP |
| 2026-03-18 | [`classes/2026-03-18-array-sum/`](classes/2026-03-18-array-sum/) | Suma de un arreglo: versión secuencial vs. versión OpenMP |
| 2026-04-06 | [`classes/2026-04-06-even-odd-split/`](classes/2026-04-06-even-odd-split/) | Separar un arreglo aleatorio en pares e impares usando aritmética de punteros |
| 2026-09-07 | [`classes/2026-09-07-calculator/`](classes/2026-09-07-calculator/) | Calculadora básica con selección de operación por carácter |

---

## Nomenclatura para ejercicios en C

Con el fin de mantener un orden claro y uniforme, los archivos de ejercicios siguen la convención:

**Formato general:**
```
<tema>_<numero>_<descripcion>.c
```

### 1. Tema
Prefijo corto que identifica la categoría:
- `cb` → C básico
- `ce` → C ejercicios intermedios
- `omp` → OpenMP
- `mpi` → MPI
- `cuda` → CUDA
- `spk` → Spark (aunque los ejemplos sean usualmente en Python o Scala)

### 2. Número
Dos dígitos para mantener orden:
```
01, 02, 03, …
```

### 3. Descripción
Breve, en inglés.
Palabras separadas por guion bajo `_`.
No más de 3–4 palabras.

**Ejemplos:**
```
cb_01_hello_world.c
cb_02_sum_array.c
ce_03_matrix_multiplication.c
omp_01_vector_sum.c
mpi_02_matrix_scatter_gather.c
cuda_01_vector_add.c
```

---

## Compilación y ejecución

La forma de compilar y ejecutar depende de la tecnología. **Compila siempre a
`.exe` o `.out`** (o dentro de `bin/` / `build/` / `output/`): esas rutas están en
`.gitignore` y los binarios no quedan versionados.

### C básico / ejercicios
```bash
gcc cb_01_hello_world.c -o cb_01_hello_world.out
./cb_01_hello_world.out
```

### OpenMP
```bash
gcc -fopenmp omp_01_vector_sum.c -o omp_01_vector_sum.out
./omp_01_vector_sum.out
```

### MPI
```bash
mpicc mpi_01_array_sum.c -o mpi_01_array_sum.out
mpiexec -n 4 ./mpi_01_array_sum.out
```

### CUDA
```bash
nvcc cuda_01_vector_add.cu -o cuda_01_vector_add
./cuda_01_vector_add
```

### Spark
```bash
spark-submit spk_01_wordcount.py
```

---

## Material de apoyo (`docs/`)

- [`docs/Guide Install C.pdf`](docs/Guide%20Install%20C.pdf) — guía de instalación del entorno de C.
- [`docs/c-tutorial/`](docs/c-tutorial/) — tutorial "C para Computación Paralela — De Cero a Intermedio" (abrir `index.html`).
- [`docs/amdahl-simulator/`](docs/amdahl-simulator/) — simulador interactivo de la Ley de Amdahl (abrir `index.html`).

---

## Datasets

Los datasets grandes (imágenes `.ppm` de la sesión 5, etc.) **no se versionan** en
git. Se conservan localmente en `_legacy/` y se documenta cómo regenerarlos en el
README de cada sesión. Ver
[`sessions/05-segmentacion-imagenes/README.md`](sessions/05-segmentacion-imagenes/README.md).

---

## Objetivo académico

Este repositorio busca servir como guía práctica y de referencia para estudiantes universitarios que se inician en la programación paralela y distribuida. El propósito es:

* Reforzar el dominio del lenguaje C como base.
* Introducir modelos de paralelismo en CPU con OpenMP.
* Presentar la programación distribuida con MPI.
* Explorar el potencial de las GPU mediante CUDA.
* Familiarizarse con el procesamiento distribuido de grandes volúmenes de datos usando Spark.

El nivel de dificultad corresponde a un curso de octavo semestre en ciencias de la computación o ingeniería de sistemas.
