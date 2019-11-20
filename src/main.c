#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "data.h"
#include "word.h"
#include "dico.h"
#include "graphe.h"
#include "dijkstra.h"
#include "monitoring.h"
#include "textVisual.h"


int main(int argc, char *argv[])
{
    printf("\n************************************************");
    printf("\n***************  du coq a l'ane  ***************");
    printf("\n************************************************\n");

    if(argc < 2){
        LIGHT_RED(printf("\nError : a dictionnary must be specified\n"))
        return 0;
    }
    if(argc > 2){
        LIGHT_RED(printf("\nError : too many arguments specified\n"))
        return 0;
    }

    char* dicoFilename = argv[1];

    T_GRAPHE Graphe;
    Graphe.sommets = NULL;
    Graphe.taille = 0;
    Graphe.wordSize = 0;

    
    MEASURE_TIME( DicoInfo dicoInfo = analyseDico(dicoFilename), "analyseDico");
    
    if(dicoInfo.wordSize == -1)
    {
        LIGHT_RED(printf("\nError : dico not valid\n"))
        return 0;
    }
    Graphe.wordSize = dicoInfo.wordSize;
    Graphe.taille = dicoInfo.wordsNumber;
    MEASURE_TIME( dico2graph(dicoFilename, &Graphe), "dico2graphe");

    while(1){
        int OK = 0;
        BOLD(printf("\nType the initial word\n");); fflush(stdout);
        char* initial_word = malloc(Graphe.wordSize*sizeof(char));
        
        while( !OK )
        {
            ITALIC(scanf("%s", initial_word);)
            if( !isWordInGraphe(initial_word, &Graphe) )
            {
                LIGHT_RED(printf("Error : the word is not in the dictionnary, type another word\n");)
                memset(initial_word, 0, Graphe.wordSize);
            }
            else
            {
                OK = 1;
            }
        }

        OK = 0;
        BOLD(printf("\nType the final word\n");)
        char* final_word = malloc(Graphe.wordSize*sizeof(char));;
        while( !OK )
        {
            ITALIC(scanf("%s", final_word);)
            if( !isWordInGraphe(final_word, &Graphe) )
            {
                LIGHT_RED(printf("Error : the word is not in the dictionnary, type another word\n"))
                memset(final_word, 0, Graphe.wordSize);
            }
            else
            {
                OK = 1;
            }
        }
        printf("\n");
        MEASURE_TIME(dijkstraAlgo(&Graphe, initial_word, final_word), "dijkstraAlgo");
    }
    return 0;
}
