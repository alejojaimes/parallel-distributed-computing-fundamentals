#include <stdio.h>

int main () {
    int x [] = {5, 8, 9, 7, 10, 11, 18};
    int count = 0;
    int f, y;
    int size = sizeof(x) / sizeof(x[0]);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ( *(x + i) == *(x + j) && i != j)
            {
             count ++;   
             if (count == 1) 
             {
                f = *(x + i);
             }
             if (count == 2) 
             {
                y = *(x + i);
             }
             
            }
            
        }   
    }
    printf("%d\n", count);
    printf("F: %d; Y: %d", f, y);
    
}