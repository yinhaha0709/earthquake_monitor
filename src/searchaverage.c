#include <stdio.h>
#include <math.h>
#include "../include/searchaverage.h"

double search_abs_average(double a[], int num)
{
    int i = 0;
    double sum = 0;
    for(i=0; i<num; i++)
        sum += fabs(a[i]);
    return sum / num;
}

double search_average(double a[], int num)
{
    int i = 0;
    double sum = 0;
    for(i=0; i<num; i++)
        sum += a[i];
    return sum / num;
}