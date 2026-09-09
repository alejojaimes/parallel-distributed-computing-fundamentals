/*
 ============================================================================
 Archivo        : read_text.c
 Autor          : Prf. Juan Alejandro Carrillo Jaimes
 Descripción    : Programa que lee un archivo de texto, cuenta las palabras
                  únicas y almacena la cantidad de veces que se repite la
                  misma palabra.
 ============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "parallelism-until-soup-clean.txt"

// define struct
typedef struct {
    char *word;  // word (save dinamically)
    int count;   // frequence
} Word;

// declare global functions
int searchWord(Word *words, int total, const char *word);
int readFile(Word **words);

// search word
int searchWord(Word *words, int total, const char *word) {
    for (int i = 0; i < total; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i; // return indef if this found
        }
    }
    return -1; // not found
}

// read file and fill list
int readFile(Word **words) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo: %s\n", FILENAME);
        return 0;
    }

    *words = NULL;     // dinamyc list of the pointer to pointers words
    int total = 0;
    char buffer[256];  // buffer foreach word

    while (fscanf(file, "%255s", buffer) == 1) {
        int index = searchWord(*words, total, buffer);

        if (index != -1) {
            (*words)[index].count++;  // if already exist increment
        } else {
            // add word and increase list dinamically
            *words = realloc(*words, (total + 1) * sizeof(Word)); // increase +1 the size of array for store one word more.
            (*words)[total].word = malloc(strlen(buffer) + 1); // reserve space for the size of word in the array for copy the text.
            strcpy((*words)[total].word, buffer); // copy the text in buffer to space reserved
            (*words)[total].count = 1; // how is the first time that the words appear, then count = 1
            total++; // increase the number of unique words registred.
        }
    }

    fclose(file);
    return total; // return the number of uniques words
}


int main() {
    Word *words = NULL;
    int total = readFile(&words);

    printf("Frecuencia de palabras:\n");
    for (int i = 0; i < total; i++) {
        printf("%s: %d\n", words[i].word, words[i].count);
        free(words[i].word); // free word
    }
    free(words); // free list

    return 0;
}