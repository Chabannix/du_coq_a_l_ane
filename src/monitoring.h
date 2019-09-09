#pragma once
#include <time.h>

clock_t begin, end;
float elapsed_time = 0;

#define MEASURE_TIME(code, msg) \ 
begin = clock(); \
code; \
end = clock(); \
elapsed_time = (float)(end - begin) / (CLOCKS_PER_SEC); \
printf("\n%s : %f ms\n", msg, elapsed_time*1000);