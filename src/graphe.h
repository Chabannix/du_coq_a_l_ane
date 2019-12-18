#ifndef GRAPHE
#define GRAPHE

#include "data.h"
#include "word.h"
#include <stdio.h>

void constructSucc(T_GRAPHE* Graphe);
int  alphabeSorting(T_GRAPHE* Graphe);
int  dico2graph(char* dico, T_GRAPHE* Graphe);
int  isWordInGraphe(char* word, T_GRAPHE* Graphe);
void displayGraphe(T_GRAPHE* Graphe);

#endif