#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void main(){
struct tm tm,tm1;
time_t t,t1;
int diff;

if (strptime("2010-02-20", "%F", &tm) == NULL)
    /* Handle error */;

if (strptime("2010-02-21", "%F", &tm1) == NULL)
    /* Handle error */;


printf("year: %d; month: %d; day: %d;\n",
        tm.tm_year, tm.tm_mon, tm.tm_mday);

printf("year: %d; month: %d; day: %d;\n",
        tm1.tm_year, tm1.tm_mon, tm1.tm_mday);




diff=difftime(tm1.tm_mday,tm.tm_mday);
printf("diff= %d",diff);

}