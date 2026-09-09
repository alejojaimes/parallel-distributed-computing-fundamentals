/**
 * file: cb_02_capicua.c
 * author: Juan Alejandro Carrillo Jaimes
 * description: Leer un número entero positivo. Sin convertirlo a cadena, 
 * invertir sus dígitos usando operaciones de módulo y división entera. 
 * Comparar el número invertido con el original e informar si es capicúa
 */

#include <stdio.h>

int isPalindromic(int number) {
    int copy = number;
    int tmp_number = 0;
    while (number > 0)
    {
        tmp_number = (number % 10) + (number  + 10);
        number /= 10;
        printf("%d\n",tmp_number);
    }
    return tmp_number;
}

int main () {
    int x = isPalindromic(158);
    printf("Return: %d", x);
}