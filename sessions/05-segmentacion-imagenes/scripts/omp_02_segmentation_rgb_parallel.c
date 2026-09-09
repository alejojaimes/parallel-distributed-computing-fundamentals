#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <imagen_entrada.ppm> <imagen_salida.ppm> <fruta>\n", argv[0]);
        printf("Ejemplo: %s red-apple.ppm salida.ppm red-apple\n", argv[0]);
        return 1;
    }

    char *pathInput = argv[1];
    char *pathOutput = argv[2];
    char *fruitType = argv[3];

    FILE *in, *out;
    char magic[3];
    int width, height, max_value;

    // --- 1. Abrir imagen ---
    in = fopen(pathInput, "rb");
    if (!in) {
        printf("No se pudo abrir la imagen de entrada.\n");
        return 1;
    }

    // --- 2. Leer cabecera PPM ---
    fscanf(in, "%2s", magic);
    fscanf(in, "%d %d", &width, &height);
    fscanf(in, "%d", &max_value);
    fgetc(in);

    // --- 3. Reservar memoria ---
    unsigned char *image = (unsigned char*) malloc(3 * width * height);
    if (!image) {
        printf("Error al asignar memoria.\n");
        fclose(in);
        return 1;
    }
    fread(image, 3, width * height, in);
    fclose(in);

    // --- 4. Definir umbrales por tipo de fruta ---
    int red_th = 120, green_th = 80, blue_th = 80;

    if (strcmp(fruitType, "red-apple") == 0) {
        red_th = 120; green_th = 80; blue_th = 80;
    } else if (strcmp(fruitType, "banana") == 0) {
        red_th = 150; green_th = 150; blue_th = 80;
    } else if (strcmp(fruitType, "pineapple") == 0) {
        red_th = 120; green_th = 130; blue_th = 100;
    } else if (strcmp(fruitType, "guarana") == 0) {
        red_th = 100; green_th = 60; blue_th = 60;
    } else if (strcmp(fruitType, "acai") == 0) {
        red_th = 60; green_th = 50; blue_th = 80;
    }

    // --- 5. Segmentación paralela ---
    #pragma omp parallel for
    for (int i = 0; i < width * height; i++) {
        unsigned char r = image[3*i];
        unsigned char g = image[3*i + 1];
        unsigned char b = image[3*i + 2];

        if (r > red_th && g < green_th && b < blue_th) {
            image[3*i]     = 255;
            image[3*i + 1] = 255;
            image[3*i + 2] = 255;
        } else {
            image[3*i]     = 0;
            image[3*i + 1] = 0;
            image[3*i + 2] = 0;
        }
    }

    // --- 6. Guardar salida ---
    out = fopen(pathOutput, "wb");
    fprintf(out, "P6\n%d %d\n%d\n", width, height, max_value);
    fwrite(image, 3, width * height, out);
    fclose(out);
    free(image);

    printf("Segmentacion Completada: %s\n", fruitType);
    return 0;
}
