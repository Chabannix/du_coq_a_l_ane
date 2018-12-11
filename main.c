#include <stdio.h>
#include <string.h>
#include "data.h"

int main()
{
	printf("****  du coq a l'ane  ****\n");

	// Process dictionnaries
	FILE* file = fopen("dico.txt", "r");
	if(file == NULL)
	{
		printf("\nError : impossible to open dictionnary file\n");
		return 0;
	}
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

	printf("\nType the initial word\n");
	char initial_word[4];
	scanf("%s", initial_word);

	printf("\nType the final word\n");
	char final_word[4];
	scanf("%s", final_word);

	return 0;
}
