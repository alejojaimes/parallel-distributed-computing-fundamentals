#include <stdio.h>

void calculator(int number_a, int number_b, char str_operator) {
    if (str_operator == '+') {
        printf("%d + %d = %d\n", number_a, number_b, (number_a + number_b));
    }
    else if (str_operator == '-') {
        printf("%d - %d = %d\n", number_a, number_b, (number_a - number_b));
    }
    else if (str_operator == '/') {
        printf("%d / %d = %.2f\n", number_a, number_b, (float)number_a / number_b);
    }
    else if (str_operator == '*') {
        printf("%d x %d = %d\n", number_a, number_b, (number_a * number_b));
    }
}

int main () {
    int number_a = 5, number_b = 10;
    calculator(number_a, number_b, '+');
    calculator(number_a, number_b, '-');
    calculator(number_a, number_b, '/');
    calculator(number_a, number_b, '*');
    return 0;
}
