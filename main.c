#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"


int dico2graph(char* dico, T_GRAPHE* Graphe)
{
	if(dico==NULL || Graphe == NULL)
		return 0;

	if(Graphe->graphe != NULL || Graphe->graphe != 0)
		return 0;

	// Open file
	FILE* file = fopen(dico, "r");
	if(file == NULL)
	{
		printf("\nError : impossible to open dictionnary file\n");
		return 0;
	}

	// Extract words from file
	char tab_words[100][50];    // 100 words of max 50 char
	int dico_processing_over = 0;
	
	int i=0;
	while(!dico_processing_over)
	{
		char * word = tab_words[i];
		if(fgets(word, 50, file) == NULL)
			dico_processing_over = 1;
		else
		{
			word[strlen(word)-1] = '\0';
			i++;
		}
	}
	Graphe->taille = i;
	Graphe->graphe = malloc(i*sizeof(T_SOMMET));

	// Stock words into graphe
	for(i=0; i<Graphe->taille; i++)
	{
		T_SOMMET sommet;
		sommet.mot = tab_words[i];
		sommet.Liste_succ = NULL;
		Graphe->graphe[i] = sommet;
	}
	return 1;
}

int main()
{
	printf("****  du coq a l'ane  ****\n");

	T_GRAPHE Graphe;
	Graphe.graphe = NULL;
	Graphe.taille = 0;

	dico2graph("dico.txt", &Graphe);

	printf("\nType the initial word\n");
	char initial_word[4];
	scanf("%s", initial_word);

	printf("\nType the final word\n");
	char final_word[4];
	scanf("%s", final_word);

	return 0;
}
