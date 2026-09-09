#!/bin/bash
# ===========================================================
# Script: process_all_fruits.sh
# Descripción:
#   Recorre todos los directorios de frutas con imágenes PPM
#   y aplica segmentación RGB en paralelo usando OpenMP (C).
#   Si los directorios de salida no existen, se crean.
# ===========================================================

# --- Paths de entrada ---
ACAI_PATH="../datasets/custom-small-fruits/preprocess-ppm/acai/"
BANANA_PATH="../datasets/custom-small-fruits/preprocess-ppm/banana/"
APPLE_PATH="../datasets/custom-small-fruits/preprocess-ppm/red-apple/"
PINEAPPLE_PATH="../datasets/custom-small-fruits/preprocess-ppm/pineapple/"
GUARANA_PATH="../datasets/custom-small-fruits/preprocess-ppm/guarana/"

# --- Paths de salida ---
ACAI_OUT_PATH="../datasets/custom-small-fruits/proccessed-ppm/acai/"
BANANA_OUT_PATH="../datasets/custom-small-fruits/proccessed-ppm/banana/"
APPLE_OUT_PATH="../datasets/custom-small-fruits/proccessed-ppm/red-apple/"
PINEAPPLE_OUT_PATH="../datasets/custom-small-fruits/proccessed-ppm/pineapple/"
GUARANA_OUT_PATH="../datasets/custom-small-fruits/proccessed-ppm/guarana/"

# --- Ruta del ejecutable ---
SCRIPT_PATH="./omp_02_segmentation_rgb_parallel.exe"

# ===========================================================
# Función: process_folder
# Descripción:
#   Crea la carpeta de salida si no existe y procesa todas las
#   imágenes .ppm del directorio de entrada.
# ===========================================================
process_folder() {
    local INPUT_DIR=$1
    local OUTPUT_DIR=$2
    local FRUIT_NAME=$3

    echo "----------------------------------------"
    echo "[INFO] Procesando imagenes desde: $INPUT_DIR"
    echo "Guardando resultados en:   $OUTPUT_DIR"
    echo "----------------------------------------"

    # Crear carpeta de salida (recursivamente)
    if [ ! -d "$OUTPUT_DIR" ]; then
        echo "Creando carpeta: $OUTPUT_DIR"
        mkdir -p "$OUTPUT_DIR"
    fi

    # Verificar que existan imágenes .ppm
    shopt -s nullglob
    files=("$INPUT_DIR"/*.ppm)
    if [ ${#files[@]} -eq 0 ]; then
        echo "[WARNING]  No se encontraron imagenes .ppm en $INPUT_DIR"
        return
    fi

    # Procesar cada imagen
    for file in "${files[@]}"; do
        filename=$(basename "$file")
        base="${filename%.ppm}"
        output_file="${OUTPUT_DIR}${base}_processed.ppm"

        echo "→ Procesando: $filename"
        "$SCRIPT_PATH" "$file" "$output_file" "$FRUIT_NAME"
    done

    echo "[FINISH] Finalizado: $INPUT_DIR"
    echo
}

# ===========================================================
# Ejecución por cada fruta
# ===========================================================
process_folder "$ACAI_PATH" "$ACAI_OUT_PATH" "acai"
process_folder "$BANANA_PATH" "$BANANA_OUT_PATH" "banana"
process_folder "$APPLE_PATH" "$APPLE_OUT_PATH" "red-apple"
process_folder "$PINEAPPLE_PATH" "$PINEAPPLE_OUT_PATH" "pineapple"
process_folder "$GUARANA_PATH" "$GUARANA_OUT_PATH" "guarana"

echo "[FINISH] Procesamiento global completado."
