#include "dijkstra.h"


void dijkstraAlgo(T_GRAPHE* Graphe, char* mot_d, char* mot_a) {
    long int d = -1;
    long int a = -1;

    /**************************************/
    /**********   Initialization **********/
    /**************************************/

    // find the index of the T_SOMMET a et d in Graphe:
    for (long int i = 0; i < Graphe->taille; i++) {
        char *mot_i = Graphe->sommets[i].mot;
        if (strcmp(mot_i, mot_d) == 0)
            d = i;
        if (strcmp(mot_i, mot_a) == 0)
            a = i;
    }

    // Construction of C
    struct T_ENSEMBLE C; // T_SOMMET which still have to be visited
    C.sommets = malloc(Graphe->taille * sizeof(T_SOMMET *));
    for (long int i = 0; i < Graphe->taille; i++) {
        C.sommets[i] = &(Graphe->sommets[i]);
    }
    C.taille = Graphe->taille;
    C.taille_max = Graphe->taille;

    // Construction of S
    struct T_ENSEMBLE S; // T_SOMMET which have been visited
    S.sommets = malloc(Graphe->taille * sizeof(T_SOMMET *));
    for (long int i = 0; i < Graphe->taille; i++) {
        S.sommets[i] = NULL;
    }
    S.taille = 0;
    S.taille_max = Graphe->taille;

    // Construction of PCC
    long int PCC[Graphe->taille];
    for (long int i = 0; i < Graphe->taille; i++) {
        if (i == d)
            PCC[i] = 0;
        else
            PCC[i] = (long int) INFINITY;
    }

    long int *parent = malloc(Graphe->taille * sizeof(long int));
    memset(parent, 0, Graphe->taille * sizeof(long int));
    long long int iteration = 0;


    /**************************************/
    /***********  dijkstra algo  **********/
    /**************************************/
    do {
        iteration++;
        printf("\rDijkstra algo : %lld iterations, C : %ld / %ld, S : %ld / %ld", iteration, C.taille, C.taille_max,
               S.taille, S.taille_max);
        fflush(stdout);

        // we look for the T_SOMMET j of C which has the lower value PCCj
        long int PCCmin = (long int) INFINITY;
        long int j = 0;
        int wordsNotConnected = 1;

        for (long int i = 0; i < Graphe->taille; i++) {
            if (C.sommets[i] == NULL)
                continue;

            if (PCC[i] < PCCmin) {
                wordsNotConnected = 0;
                PCCmin = PCC[i];
                j = i;
            }
        }

        // if all words in C have an infinite PCC : it means that S and C have no connections anymore,
        // the updates of PCC in S are not affecting any words (and their PCC) in C
        // -> the algo is over, there is no path between the 2 words
        if (wordsNotConnected) {
            LIGHT_RED(printf("\nNo path found from %s to %s\n", Graphe->sommets[d].mot, Graphe->sommets[a].mot))
            return;
        }

        // otherwise we keep updating C and S
        T_SOMMET *sommet_j = &(Graphe->sommets[j]);

        if (S.sommets[j] == NULL) {
            S.sommets[j] = sommet_j;
            S.taille++;
        }
        if (C.sommets[j] != NULL) {
            C.sommets[j] = NULL;
            C.taille--;
        }

        // Update the PCCk for all the T_SOMMET k adjacent to j
        L_SUCC succ_k = sommet_j->Liste_succ;
        while (succ_k != NULL) {
            long int k = findSommet(succ_k->val, Graphe);
            if (PCC[k] > PCC[j] + 1) {
                PCC[k] = PCC[j] + 1;
                parent[k] = j;
            }
            succ_k = succ_k->suiv;
        }
    } while (isSommetInEnsemble(S, &Graphe->sommets[a]) == 0);

    LIGHT_GREEN(displaySolution(Graphe, parent, d, a));
}


void displaySolution(T_GRAPHE* Graphe, long int *parent, long int d, long int a)
{
    // Warning : infinite loop if no solution exists
    // the existence of a solution must be checked by the caller before calling this function

    int over = 0;
    long int k = a;
    int lengthSolution = 0;
    printf("\n");

    while( !over )
    {
        char* word = Graphe->sommets[k].mot;
        printf("%s", word);
        if(k==d)
        {
            over = 1;
        }
        else
        {
            printf(" <-- ");
            k = parent[k];
            lengthSolution++;
        }
    }
    printf("\nLength solution : %d words\n", lengthSolution);
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

int isSommetInEnsemble(struct T_ENSEMBLE S, T_SOMMET* a)
{
    for(long int i=0; i< S.taille; i++)
    {
        if(S.sommets[i] == a)
            return 1;
    }
    return 0;
}