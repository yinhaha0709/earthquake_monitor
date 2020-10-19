#include <stdio.h>
#include "../include/searchmax.h"

double search_max(double a[], int num)
{
    int i = 0;
    double max = -1.0;
    for(i=0; i<num; i++)
    {
        if(a[i] > max)
            max = a[i];
    }

    return max;
}