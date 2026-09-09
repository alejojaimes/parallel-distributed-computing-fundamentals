#include <stdio.h>

void sum_number(int *x) {
    *x += 1;
}

int main () {
    int x = 5;
    printf("Before X: %d\n", x);
    
    sum_number(&x);

    printf("After X: %d\n", x);



    return 0;
}