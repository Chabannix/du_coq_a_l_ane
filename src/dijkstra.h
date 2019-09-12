#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "data.h"
#include <math.h>
#include <stdio.h>

struct T_ENSEMBLE
{
    T_SOMMET** sommets;
    long int taille;
    long int taille_max;
};

void dijkstraAlgo(T_GRAPHE* Graphe, char* mot_d, char* mot_a);
long int findSommet(T_SOMMET* sommet, T_GRAPHE* Graphe);
int check_a_in_S(struct T_ENSEMBLE S, T_SOMMET* a);

void dijkstraAlgo(T_GRAPHE* Graphe, char* mot_d, char* mot_a)
{
    long int d = -1;
    long int a = -1;

    // find the index of the T_SOMMET a et d in Graphe:
    for(long int i=0; i<Graphe->taille; i++)
    {
        char* mot_i = Graphe->sommets[i].mot;
        if( strcmp(mot_i, mot_d)==0 )
            d = i;
        if( strcmp(mot_i, mot_a)==0 )
            a = i;
    }

    // Construction of C
    struct T_ENSEMBLE C; // T_SOMMET which still have to be visited
    C.sommets = malloc(Graphe->taille*sizeof(T_SOMMET*));
    for(long int i=0; i<Graphe->taille; i++)
    {
        C.sommets[i] = &(Graphe->sommets[i]);
    }
    C.taille = Graphe->taille;
    C.taille_max = Graphe->taille;

    // Construction of S
    struct T_ENSEMBLE S; // T_SOMMET which have been visited
    S.sommets = malloc(Graphe->taille*sizeof(T_SOMMET*));
    for(long int i=0; i<Graphe->taille; i++)
    {
        S.sommets[i] = NULL;
    }
    S.taille = 0;
    S.taille_max = Graphe->taille;

    // Construction of PCC
    long int PCC[Graphe->taille];
    for(long int i=0; i<Graphe->taille; i++)
    {
        if(i == d)
            PCC[i] = 0;
        else
            PCC[i] = (long int)INFINITY;
    }

    long int* parent = malloc(Graphe->taille * sizeof(long int));
    memset(parent, 0, Graphe->taille*sizeof(long int));
    long long int iteration = 0;
    do{
        iteration++;

        // we look for the T_SOMMET j of C which has the lower value PCCj
        long int PCCmin = (long int)INFINITY;
        long int j = 0;
        int wordsNotConnected = 1;

        for(long int i=0; i<Graphe->taille; i++)
        {
            if(C.sommets[i] == NULL)
                continue;

            if(PCC[i] < PCCmin)
            {
                wordsNotConnected = 0;
                PCCmin = PCC[i];
                j = i;
            }
        }

        // if all words in C have an infinite PCC : it means that S and C have not connections anymore,
        // the updates of PCC in S are not affecting any words (and their PCC) in C
        // -> the algo is over, the is no path bewteen the 2 words
        if(wordsNotConnected){
            printf("\rNo path found from %s to %s", Graphe->sommets[d].mot, Graphe->sommets[a].mot);
            return;
        }


        // otherwise we keep updating C and S
        T_SOMMET* sommet_j =  &(Graphe->sommets[j]);

        if(S.sommets[j] == NULL){
            S.sommets[j] = sommet_j;
            S.taille++;
        }
        if(C.sommets[j] != NULL){
            C.sommets[j] = NULL;
            C.taille--;
        }

        printf("\rDijkstra algo : %lld iterations, C : %ld / %ld, S : %ld / %ld", iteration, C.taille, C.taille_max, S.taille, S.taille_max); fflush(stdout);

        // Update of the PCCk for all the T_SOMMET k adjacent to j
        L_SUCC succ_k = sommet_j->Liste_succ;
        while(succ_k != NULL)
        {
            long int k = findSommet(succ_k->val, Graphe);
            if(PCC[k] > PCC[j] + 1)
            {
                PCC[k] = PCC[j] + 1;
                parent[k] = j;
            }
            succ_k = succ_k->suiv;
        }
    }while( check_a_in_S(S, &Graphe->sommets[a]) == 0 );


    // display the solution
    int over = 0;
    long int k = a;
    printf("\n");

    while( !over )
    {
        char* word = Graphe->sommets[k].mot;
        printf("%s", word);
        if(k==d)
        {
            printf("\n");
            over = 1;
        }
        else
        {
            printf("->");
            k = parent[k];
        }
    }
}

long int findSommet(T_SOMMET* sommet, T_GRAPHE* Graphe)
{
    // check if sommet is in Graphe and return the corresponding index i, return -1 if not present
    for(long int i=0; i<Graphe->taille; i++)
    {
        if(&Graphe->sommets[i] == sommet)
        {
            return i;
        }
    }
    return -1;
}

int check_a_in_S(struct T_ENSEMBLE S, T_SOMMET* a)
{
    for(long int i=0; i< S.taille; i++)
    {
        if(S.sommets[i] == a)
            return 1;
    }
    return 0;
}

#endif