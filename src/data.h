#ifndef DATA_H
#define DATA_H

struct T_SOMMET;

typedef struct T_SOMMET* T_SUCC;
typedef struct T_SOMMET  T_SOMMET;
typedef struct lsucc*    L_SUCC;
typedef struct DicoInfo DicoInfo;

struct lsucc
{
    T_SUCC val;
    struct lsucc* suiv;
};

struct T_SOMMET
{
    char* mot; 
    L_SUCC Liste_succ;
};

typedef struct 
{
    T_SOMMET* sommets;
    long  int taille;
    int wordSize;
} T_GRAPHE;

struct DicoInfo
{
    int wordSize;
    long int wordsNumber;
};

#endif
