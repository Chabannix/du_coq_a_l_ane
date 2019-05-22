#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "word.h"
#include "dico.h"
#include "graphe.h"
#include "dijsktra.h"

int main()
{
	printf("****  du coq a l'ane  ****\n");

	T_GRAPHE Graphe;
	Graphe.sommets = NULL;
	Graphe.taille = 0;

    dico2graph("dico.txt", &Graphe);
    displayGraphe(&Graphe);

	int OK = 0;
	printf("\nType the initial word\n");
	char* initial_word = malloc(4*sizeof(char));

	while( !OK )
	{
        scanf("%s", initial_word);

		if( !isWordInGraphe(initial_word, &Graphe) )
		{
			fprintf(stderr, "Error : the word is not in the dictionnary, type another word\n");
			memset(initial_word, 0, 4);
		}
		else
		{
			OK = 1; 
		}
	}

	OK = 0;
	printf("\nType the final word\n");
	char* final_word = malloc(4*sizeof(char));;
	while( !OK )
	{
        scanf("%s", final_word);
		if( !isWordInGraphe(final_word, &Graphe) )
		{
			fprintf(stderr, "Error : the word is not in the dictionnary, type another word\n");
			memset(final_word, 0, 4);
		}
		else
		{
			OK = 1; 
		}
	}

    dijsktraAlgo(&Graphe, initial_word, final_word);
	
	return 0;
}
