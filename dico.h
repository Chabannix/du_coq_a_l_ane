#ifndef DICO
#define DICO

#include "data.h"
#include <stdio.h>

DicoInfo analyseDico(char * filename);

DicoInfo analyseDico(char * filename)
{
    DicoInfo ret;
    ret.wordSize = 0;
    ret.wordsNumber = 0;

    FILE* file = fopen(filename, "r");
    if(file == NULL)
        return (DicoInfo){-1,-1};

    // Analyse the first word to set wordSize
    char c = fgetc(file);
    while(c != '\n' && c != EOF)
    {
        ret.wordSize++;
        c = fgetc(file);
    }

    // Anlyse the others words
    int end_reached = 0;
    while( !end_reached )
    {
        ret.wordsNumber++;
        int wordSize = 0;
        c = fgetc(file);

        // Analyse of the current world size
        while(c != '\n' && c != EOF)
        {
            wordSize++;
            c = fgetc(file);
        }
        if(wordSize > 0 && wordSize != ret.wordSize)
        {
            printf("\nError : several words have not the same size : \n word 1 has %d letters while word %ld has %d letters", ret.wordSize, ret.wordsNumber, wordSize);
            fclose(file);
            return (DicoInfo){-1,-1};
        }
        if(c == EOF)
            end_reached = 1;
    }
    fclose(file);
    return ret;
}

#endif