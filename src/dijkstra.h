#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "data.h"
#include <math.h>
#include <stdio.h>
#include "textVisual.h"

struct T_ENSEMBLE
{
    T_SOMMET** sommets;
    long int taille;
    long int taille_max;
};

void     dijkstraAlgo(T_GRAPHE* Graphe, char* mot_d, char* mot_a);
long int findSommet(T_SOMMET* sommet, T_GRAPHE* Graphe);
int      isSommetInEnsemble(struct T_ENSEMBLE S, T_SOMMET* a);
void     displaySolution(T_GRAPHE* Graphe, long int *parent, long int d, long int a);

#endif