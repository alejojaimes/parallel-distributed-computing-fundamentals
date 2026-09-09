#include <stdio.h>

int main () {
    // Declare pointer value assignement
    int value = 5;
    int *p = &value;

    printf("value: %d , and pointer value: %d", value, *p);

    // Change value by pointer
    *p = 15;
    printf("value: %d , and pointer value", value, *p);


    return 0;
}