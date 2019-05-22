#ifndef WORD
#define WORD

#include "data.h"

int isAlphabeSorted(char* word1, char* word2, int wordSize);
int isSucc(char* word1, char* word2, int wordSize);

int isAlphabeSorted(char* word1, char* word2, int wordSize)
{
    for(int i=0; i<wordSize; i++)
    {
        if(word1[i] < word2[i])
            return 1;
        if(word1[i] > word2[i])
            return 0;
    }

    //it's the same word
    return 0;
}

int isSucc(char* word1,char* word2, int wordSize)
{
    int count_letters_in_common = 0;
    for(int i=0; i<wordSize; i++)
    {
        if(word1[i] == word2[i])
            count_letters_in_common++;
    }
    if(count_letters_in_common==3)
        return 1;
    else
        return 0;
}
#endif