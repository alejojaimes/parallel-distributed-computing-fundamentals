# Sesión 5 — Segmentación de imágenes en paralelo

Segmentación de imágenes PPM (formato `P6`) usando OpenMP.

## Contenido

| Archivo | Descripción |
|---------|-------------|
| `scripts/omp_01_segmentation_binary.c` | Umbralización binaria de una imagen PPM |
| `scripts/omp_02_segmentation_rgb_parallel.c` | Segmentación RGB en paralelo (OpenMP), por fruta |
| `scripts/shell_execute_02_segment_rgb_parallel.sh` | Recorre todas las carpetas de frutas y aplica la segmentación RGB |
| `script.sh` | Utilidad simple: lista las imágenes `.ppm` de una carpeta |

## Compilar

```bash
cd scripts
gcc -fopenmp -O2 omp_01_segmentation_binary.c -o omp_01_segmentation_binary.out
gcc -fopenmp -O2 omp_02_segmentation_rgb_parallel.c -o omp_02_segmentation_rgb_parallel.out
```

## Dataset

Las imágenes (`custom-small-fruits/`, ~52 MB de archivos `.ppm`) **no se versionan**
en git. Se conservan localmente en `_legacy/session5-datasets/`.

Para trabajar con los scripts, restaura el dataset dentro de esta carpeta:

```bash
# desde la raíz del repo
cp -r _legacy/session5-datasets/custom-small-fruits \
      sessions/05-segmentacion-imagenes/datasets/custom-small-fruits
```

La estructura esperada es:

```
datasets/custom-small-fruits/
├── preprocess-ppm/        # entrada: <fruta>/<fruta>_NN_test_preprocess.ppm
│   ├── acai/  banana/  guarana/  pineapple/  red-apple/
└── proccessed-ppm/        # salida generada por los scripts
```

Los `.ppm` están en `.gitignore`, así que aunque restaures la carpeta no volverán
a quedar versionados.
