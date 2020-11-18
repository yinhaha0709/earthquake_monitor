#include <stdio.h>
#include "../include/searchmin.h"

double search_min(double a[], int num)
{
    int i = 0;
    double min = 5.0;
    for(i=0; i<num; i++)
    {
        if(a[i] < min)
            min = a[i];
    }

    return min;
}