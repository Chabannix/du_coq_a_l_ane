#pragma once

#define BLACK(code)         printf("\e[30m"); code; printf("\e[0m");
#define RED(code)           printf("\e[31m"); code; printf("\e[0m");
#define GREEN(code)         printf("\e[32m"); code; printf("\e[0m");
#define YELLOW(code)        printf("\e[33m"); code; printf("\e[0m");
#define BLUE(code)          printf("\e[34m"); code; printf("\e[0m");
#define MAGENTA(code)       printf("\e[35m"); code; printf("\e[0m");
#define CYAN(code)          printf("\e[36m"); code; printf("\e[0m");
#define LIGHT_GRAY(code)    printf("\e[37m"); code; printf("\e[0m");
#define DARK_GRAY(code)     printf("\e[90m"); code; printf("\e[0m");
#define LIGHT_RED(code)     printf("\e[91m"); code; printf("\e[0m");
#define LIGHT_GREEN(code)   printf("\e[92m"); code; printf("\e[0m");
#define LIGHT_YELLOW(code)  printf("\e[93m"); code; printf("\e[0m");
#define LIGHT_BLUE(code)    printf("\e[94m"); code; printf("\e[0m");
#define LIGHT_MAGENTA(code) printf("\e[95m"); code; printf("\e[0m");
#define LIGHT_CYAN(code)    printf("\e[96m"); code; printf("\e[0m");
#define WHITE(code)         printf("\e[97m"); code; printf("\e[0m");


#define BOLD(code)       printf("\e[1m"); code; printf("\e[0m");
#define DIM (code)       printf("\e[2m"); code; printf("\e[0m");
#define ITALIC(code)     printf("\e[3m"); code; printf("\e[0m");
#define UNDERLINED(code) printf("\e[4m"); code; printf("\e[0m");
#define BLINK(code)      printf("\e[5m"); code; printf("\e[0m");
#define REVERSE(code)    printf("\e[7m"); code; printf("\e[0m");
#define HIDDEN(code)     printf("\e[8m"); code; printf("\e[0m");