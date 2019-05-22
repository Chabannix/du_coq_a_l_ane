#ifndef GRAPHE
#define GRAPHE

#include "data.h"

void constructSucc(T_GRAPHE* Graphe);
int alphabeSorting(T_GRAPHE* Graphe);
int dico2graph(char* dico, T_GRAPHE* Graphe);
int isWordInGraphe(char* word, T_GRAPHE* Graphe);
void displayGraphe(T_GRAPHE* Graphe);

void constructSucc(T_GRAPHE* Graphe)
{
    if(Graphe == NULL)
        return;

    for(int i=0; i<Graphe->taille; i++)
    {
        char* word1 = Graphe->sommets[i].mot;
        for(int j=0; j<Graphe->taille; j++)
        {
            if(j==i)
                continue;

            char* word2 = Graphe->sommets[j].mot;
            if( isSucc(word1, word2, Graphe->wordSize) )
            {
                L_SUCC* Liste_succ = &Graphe->sommets[i].Liste_succ;

                while(*Liste_succ != NULL)
                    Liste_succ = &((*Liste_succ)->suiv);

                (*Liste_succ) = malloc(sizeof(struct lsucc));
                (*Liste_succ)->val = &Graphe->sommets[j];
            }

        }
    }
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
            char* word1 = Graphe->sommets[i].mot;
            char* word2 = Graphe->sommets[i+1].mot;

            // compare the 2 words and swap them if need be
            if( !isAlphabeSorted(word1, word2, Graphe->wordSize) )
            {
                sorting_over = 0;
                char tmp[Graphe->wordSize];
                memcpy(tmp, word2, Graphe->wordSize);
                memcpy(word2, word1, Graphe->wordSize);
                memcpy(word1, tmp, Graphe->wordSize);
            }
        }
        size--;
    }
    return 1;
}

int dico2graph(char* dico, T_GRAPHE* Graphe)
{
    if(dico==NULL || Graphe == NULL)
        return 0;

    if(Graphe->sommets != NULL)
        return 0;

    // Open file
    FILE* file = fopen(dico, "r");
    if(file == NULL)
    {
        printf("\nError : impossible to open dictionnary file\n");
        return 0;
    }

    // Extract words from file
    char tab_words[Graphe->taille][Graphe->wordSize+1];    // 100 words of max 50 char
    int dico_processing_over = 0;

    int i=0;
    while(!dico_processing_over)
    {
        char * word = tab_words[i];
        if(fgets(word, Graphe->wordSize+10, file) == NULL)
            dico_processing_over = 1;
        else
        {
            word[Graphe->wordSize] = '\0';
            i++;
        }
    }
    if(i != Graphe->taille)
    {
        printf("\nError in dico2graphe ligne %d\n", __LINE__);
    }
    Graphe->sommets = malloc(i*sizeof(T_SOMMET));
    // Stock words into graphe
    for(i=0; i<Graphe->taille; i++)
    {
        T_SOMMET sommet;
        sommet.mot = tab_words[i];
        sommet.Liste_succ = NULL;
        Graphe->sommets[i] = sommet;
    }
    alphabeSorting(Graphe);
    constructSucc(Graphe);
    return 1;
}

int isWordInGraphe(char* word, T_GRAPHE* Graphe)
{
    char* word0 = Graphe->sommets[0].mot;
    if(word == NULL || Graphe == NULL)
        return 0;

    for(int i=0; i<Graphe->taille; i++)
    {
        char* toto = Graphe->sommets[i].mot;
        if( strcmp(Graphe->sommets[i].mot, word)==0 )
            return 1;
    }
    return 0;
}

void displayGraphe(T_GRAPHE* Graphe)
{
    if(Graphe == NULL)
        return;
    printf("\ntaille = %d", Graphe->taille);

    for(int i=0; i<Graphe->taille; i++)
    {
        printf("\ngraphe[%d].mot = %s", i, Graphe->sommets[i].mot);
        L_SUCC Liste_succ = Graphe->sommets[i].Liste_succ;

        while(Liste_succ != NULL)
        {
            printf("->%s", Liste_succ->val->mot);
            Liste_succ = Liste_succ->suiv;
        }
    }
    printf("\n\n");
}


#endif