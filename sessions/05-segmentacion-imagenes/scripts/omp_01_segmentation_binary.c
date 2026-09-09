// simple_image_threshold.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <imagen_entrada.ppm> <imagen_salida.ppm>\n", argv[0]);
        return 1;
    }

    char *pathInput = argv[1];
    char *pathOutput = argv[2];


    FILE *in, *out;
    char magic[3];
    int width, height, max_value;

    // --- 1. Abrir imagen de entrada ---
    in = fopen(pathInput, "rb");
    if (!in) {
        printf("No se pudo abrir la imagen.\n");
        return 1;
    }

    // --- 2. Leer cabecera del archivo PPM ---
    fscanf(in, "%2s", magic);     // debe ser "P6"
    fscanf(in, "%d %d", &width, &height);
    fscanf(in, "%d", &max_value);
    fgetc(in); // consumir salto de línea

    // --- 3. Crear arreglo para todos los píxeles (RGB) ---
    unsigned char image[height][width][3];

    // --- 4. Leer datos de la imagen ---
    fread(image, 3, width * height, in);
    fclose(in);

    // --- 5. Definir umbral (brillo medio) ---
    int threshold = 120;

    // --- 6. Procesar la imagen en paralelo ---
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char r = image[i][j][0];
            unsigned char g = image[i][j][1];
            unsigned char b = image[i][j][2];

            // calcular brillo promedio
            int brightness = (r + g + b) / 3;
            //printf("Brillo de imagen: %d\n", brightness);

            if (brightness > threshold) {
                // píxel claro → blanco
                image[i][j][0] = 255;
                image[i][j][1] = 255;
                image[i][j][2] = 255;
            } else {
                // píxel oscuro → negro
                image[i][j][0] = 0;
                image[i][j][1] = 0;
                image[i][j][2] = 0;
            }
        }
    }

    // --- 7. Guardar resultado en nuevo archivo ---
    out = fopen(pathOutput, "wb");
    fprintf(out, "P6\n%d %d\n%d\n", width, height, max_value);
    fwrite(image, 3, width * height, out);
    fclose(out);

    printf("✅ Imagen procesada y guardada como salida.ppm\n");
    return 0;
}
