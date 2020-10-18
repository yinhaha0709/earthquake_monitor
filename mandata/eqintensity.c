#include <stdio.h>
#include "../include/eqintensity.h"

int earthquake_intensity(double peakAcc)
{
    int Y = 1000 * peakAcc;
    int L = 0;

    if(Y >= 20 && Y <= 25)
        L = 4;
    else if(Y > 25 && Y <=50)
        L = 5;
    else if(Y > 50 && Y <= 100)
        L = 6;
    else if(Y > 100 && Y <= 200)
        L = 7;
    else if(Y > 200 && Y <=350)
        L = 8;
    else if(Y > 350)
        L = 9;
    else
        L = 0;

    return L;
}