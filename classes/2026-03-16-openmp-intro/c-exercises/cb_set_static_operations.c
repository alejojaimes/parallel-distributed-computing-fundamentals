#include <stdio.h>

int contains(int *arr, int size, int value) {
    // Buscar en el arr, si existe value
    // devolver True/False.
    for (int i = 0; i < size; i++)
    {
        if ( *(arr + i) == value) {
            return 1;
        }
    }
    return 0; 
}


int main () {
    // 1. Entender el problema.
    // 2. Definir dos conjuntos con valores estaticos
    //   2.1 set_a = {1, 2, 4, 5}
    //   2.2 set_b = {3, 6, 4, 5}
    int set_a [] = {1, 2, 4, 5, 9};
    int set_b [] = {3, 6, 4, 5};
    //   2.3 Determinar tamanios arrays
    int size_a = sizeof(set_a) / sizeof(set_a[0]);
    int size_b = sizeof(set_b) / sizeof(set_b[0]);

    if (contains(set_a, size_a, 17))
    {
        printf("Exists.\n");
    } else
    {
        printf("No Exists.\n");
    }
    
    

    // 3. Crear una funcion para union
    // 4. Crear una funcion para interseccion




    return 0;
}