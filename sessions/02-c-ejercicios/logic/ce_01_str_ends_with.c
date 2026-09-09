#include <stdio.h>
#include <stdbool.h>

int length(const char *string) {
    int len = 0;
    while (string[len] != '\0')
    {
        len++;
    }
    return len;
}

bool solution(const char *string, const char *ending) {
    // get exact length of each string
    int stringLength = length(string);
    int endingLength = length(ending);

    // Check if ending is longer return false.
    if (endingLength > stringLength)
    {
        return false;
    }

    // Compare char by char from the end
    for (int i = 0; i < endingLength; i++) 
    {
        int posChar = (stringLength - endingLength) + i ;
        if (string[posChar] != ending[i])
        {
            return false;
        }
        
    }
    return true;
}

int main () {
    printf("%d\n", solution("abc", "bc"));
    printf("%d", solution("abc", "d"));
    return 0;
}