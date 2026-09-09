#include <stdio.h>
#include <ctype.h>

/*
Make an algorithm that count chars
in string
*/

int count_words(char *string) {
    int words = 0, in_word = 0;
    while (*string != '\0') {
        if (isspace((unsigned char)*string)) {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            words++;
        }
        string++;
    }
    return words;
}


int main() {
    char text[] = "Hello world, this is and exercise of pointers";

    printf("Text: \"%s\"\n", text);
    printf("Total words: %d", count_words(text));
}