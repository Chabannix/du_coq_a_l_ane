#pragma once
#include <time.h>
#include "textVisual.h"

clock_t begin, end;
long double elapsed_time = 0;

#define MEASURE_TIME(code, msg) \
begin = clock(); \
code; \
end = clock(); \
elapsed_time = (float)(end - begin) / (CLOCKS_PER_SEC); \
if(elapsed_time > 1){ \
    DARK_GRAY(printf("\n%s : %Lf sec\n", msg, elapsed_time)) \
}\
else{ \
    DARK_GRAY(printf("\n%s : %Lf ms\n", msg, elapsed_time*1000)) \
}