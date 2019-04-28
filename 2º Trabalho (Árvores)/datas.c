#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define _XOPEN_SOURCE /* glibc2 needs this */

int main(){


    struct tm date1, date2;
    strptime( "2017-03-21", "%F", &date1 );
    strptime( "2018-01-20", "%F", &date2 );
    printf("%.0lf\n", difftime(mktime(&date1), mktime(&date2)));
    return 0;
}