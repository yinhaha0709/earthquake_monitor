#include <stdio.h>
#include <math.h>
#include "../include/eqintensity.h"
#include "../include/config.h"
#include "../include/searchmax.h"

void earthquake_intensity(double a[], int n)
{
    int i;

    double b[n];
    
    double max_temp = 0;
    
    for(i=0; i<n; i++)
    {
        b[i] = fabs(a[i]);
    }

    max_temp = search_max(b, n);

    if((float)max_temp > sig_max){
        sig_max = (float)max_temp;
    }

    if(sig_max >= 0.020){
        earthquake_status = 1;
    }
}