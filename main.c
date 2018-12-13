#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"


int dico2graph(char* dico, T_GRAPHE* Graphe);
int isWordInGraphe(char* word, T_GRAPHE* Graphe);
void displayGraphe(T_GRAPHE* Graphe);
int isAlphabeSorted(char word1[4], char word2[4]);
int alphabeSorting(T_GRAPHE* Graphe);
void constructSucc(T_GRAPHE* Graphe);
int isSucc(char word1[4],char word2[4]);

int dico2graph(char* dico, T_GRAPHE* Graphe)
{
	if(dico==NULL || Graphe == NULL)
		return 0;

	if(Graphe->graphe != NULL || Graphe->taille != 0)
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
	alphabeSorting(Graphe);
	constructSucc(Graphe);
	return 1;
}

int alphabeSorting(T_GRAPHE* Graphe)
{
	if(Graphe == NULL)
		return 0;
	
	// Bubble sorting
	int size = Graphe->taille;
	int sorting_over = 0;
	while( !sorting_over )
	{
		sorting_over = 1;
		for(int i=0; i<size-1; i++)
		{
			char* word1 = Graphe->graphe[i].mot;
			char* word2 = Graphe->graphe[i+1].mot;

			// compare the 2 words and swap them if need be
			if( !isAlphabeSorted(word1,word2) )
			{
				sorting_over = 0;
				char tmp[4];
                memcpy(tmp, word2, 4);
                memcpy(word2, word1, 4);
                memcpy(word1, tmp, 4);
			}
		}
		size--;
	}
	return 1;
}

int isAlphabeSorted(char word1[4], char word2[4])
{
	for(int i=0; i<4; i++)
	{
		if(word1[i] < word2[i])
			return 1;
		if(word1[i] > word2[i])
			return 0;
	}

	//it's the same word
	return 0;
}

int isWordInGraphe(char* word, T_GRAPHE* Graphe)
{
	if(word == NULL || Graphe == NULL)
		return 0;
		
	for(int i=0; i<Graphe->taille; i++)
	{	
		if( strcmp(Graphe->graphe[i].mot, word)==0 )
			return 1;
	}
	return 0;
}

void constructSucc(T_GRAPHE* Graphe)
{
	if(Graphe == NULL)
		return;
		
	for(int i=0; i<Graphe->taille; i++)
	{	
		char* word1 = Graphe->graphe[i].mot;
		for(int j=0; j<Graphe->taille; j++)
		{
			if(j==i)
				continue;

			char* word2 = Graphe->graphe[j].mot;
			if( isSucc(word1,word2) )
			{
				L_SUCC* Liste_succ = &Graphe->graphe[i].Liste_succ;

				while(*Liste_succ != NULL)
					Liste_succ = &((*Liste_succ)->suiv);

                (*Liste_succ) = malloc(sizeof(struct lsucc));
                (*Liste_succ)->val = &Graphe->graphe[j];
			}
			
		}
	}
}

int isSucc(char word1[4],char word2[4])
{
	int count_letters_in_common = 0;
	for(int i=0; i<4; i++)
	{
		if(word1[i] == word2[i])
			count_letters_in_common++;
	}
	if(count_letters_in_common==3)
		return 1;
	else
		return 0;
}

void displayGraphe(T_GRAPHE* Graphe)
{
	if(Graphe == NULL)
		return;
	printf("\ntaille = %d", Graphe->taille);

	for(int i=0; i<Graphe->taille; i++)
	{
		printf("\ngraphe[%d].mot = %s", i, Graphe->graphe[i].mot);
		L_SUCC Liste_succ = Graphe->graphe[i].Liste_succ;

		while(Liste_succ != NULL)
		{
			printf("->%s", Liste_succ->val->mot);
			Liste_succ = Liste_succ->suiv;
		}
	}
	printf("\n\n");
}

int main()
{
	printf("****  du coq a l'ane  ****\n");

	T_GRAPHE Graphe;
	Graphe.graphe = NULL;
	Graphe.taille = 0;

	dico2graph("dico.txt", &Graphe);

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
    displayGraphe(&Graphe);

	return 0;
}
