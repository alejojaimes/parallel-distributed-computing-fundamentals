/**
 * Prime numbers:
 * 
 * Create a program that determine if a number is prime or not.
 * 
 * Use this mathematical property:
 * If a number n has divisors grather than sqrt(n), then need has a divisor pair
 * that is lower that sqrt(n)
 * 
 * Example:
 * 
 * n = 13
 * sqrt(13) => 3.6
 * i = 2, 3
 * two iterations
 */


#include <stdio.h>

int is_prime(int number) {
    for (int i = 2; i * i <= number; i++)
    {
        if (number % i == 0)
        {
            return 0;
        }
        
    }
    
    return 1;
}

int main () {
    
   return 0;
}