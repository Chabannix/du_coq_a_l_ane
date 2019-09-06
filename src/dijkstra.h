#ifndef DIJSKTRA_H
#define DIJSKTRA_H

#include "data.h"
#include <math.h>
#include <stdio.h>

struct T_ENSEMBLE
{
    T_SOMMET** sommets;
    long int taille;
};

void dijsktraAlgo(T_GRAPHE* Graphe, char* mot_d, char* mot_a);
long int findSommet(T_SOMMET* sommet, T_GRAPHE* Graphe);
int check_a_in_S(struct T_ENSEMBLE S, T_SOMMET* a);

void dijsktraAlgo(T_GRAPHE* Graphe, char* mot_d, char* mot_a)
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

    // Construction of S
    struct T_ENSEMBLE S; // T_SOMMET which still have to be visited
    S.sommets = malloc(Graphe->taille*sizeof(T_SOMMET*));
    for(long int i=0; i<Graphe->taille; i++)
    {
        S.sommets[i] = NULL;
    }
    S.taille = Graphe->taille;

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
    do{
        // we look for the T_SOMMET j of C which has the lower value PCCj
        long int PCCmin = (long int)INFINITY;
        long int j = 0;
        for(long int i=0; i<Graphe->taille; i++)
        {
            if(C.sommets[i] == NULL)
                continue;

            if(PCC[i] < PCCmin)
            {
                PCCmin = PCC[i];
                j = i;
            }
        }
        T_SOMMET* sommet_j =  &(Graphe->sommets[j]);

        // Update S and C
        S.sommets[j] = sommet_j;
        C.sommets[j] = NULL;

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


