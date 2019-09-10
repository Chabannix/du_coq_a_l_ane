#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "data.h"
#include "word.h"
#include "dico.h"
#include "graphe.h"
#include "dijkstra.h"
#include "monitoring.h"

int main()
{
    printf("****  du coq a l'ane  ****\n");

    T_GRAPHE Graphe;
    Graphe.sommets = NULL;
    Graphe.taille = 0;
    Graphe.wordSize = 0;

    char* dicoFilename = "../dico/umot5.txt";
    
    MEASURE_TIME( DicoInfo dicoInfo = analyseDico(dicoFilename), "analyseDico");
    
    if(dicoInfo.wordSize == -1)
    {
        printf("\nError : dico not valid\n");
        return 0;
    }
    Graphe.wordSize = dicoInfo.wordSize;
    Graphe.taille = dicoInfo.wordsNumber;
    dico2graph(dicoFilename, &Graphe);

    int OK = 0;
    printf("\nType the initial word\n");
    char* initial_word = malloc(Graphe.wordSize*sizeof(char));

    while( !OK )
    {
        scanf("%s", initial_word);
        if( !isWordInGraphe(initial_word, &Graphe) )
        {
            fprintf(stderr, "Error : the word is not in the dictionnary, type another word\n");
            memset(initial_word, 0, Graphe.wordSize);
        }
        else
        {
            OK = 1;
        }
    }

    OK = 0;
    printf("\nType the final word\n");
    char* final_word = malloc(Graphe.wordSize*sizeof(char));;
    while( !OK )
    {
        scanf("%s", final_word);
        if( !isWordInGraphe(final_word, &Graphe) )
        {
            fprintf(stderr, "Error : the word is not in the dictionnary, type another word\n");
            memset(final_word, 0, Graphe.wordSize);
        }
        else
        {
            OK = 1;
        }
    }
    MEASURE_TIME(dijkstraAlgo(&Graphe, initial_word, final_word), "dijkstraAlgo");

    return 0;
}
