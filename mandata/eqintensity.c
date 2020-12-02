#include <stdio.h>
//#include <math.h>
#include "../include/eqintensity.h"
#include "../include/config.h"
#include "../include/searchmax.h"
#include "../include/searchmin.h"

float sig_max, sig_min;

void earthquake_intensity(double a[], int n)
{
    int i;
    //double b[n];
    float max_temp, min_temp;

    for (i = 0; i < n; i++)
    {
        //b[i] = fabs(a[i]);
        if ((a[i] >= 0.020) || (a[i] <= -0.020))
        {
            threshold_status[i] = 1;
            earthquake_status = 1;
        }
    }

    if (earthquake_status == 1)
    {
        max_temp = (float)search_max(a, n);
        min_temp = (float)search_min(a, n);

        if (max_temp > sig_max)
        {
            sig_max = max_temp;
        }

        if (min_temp < sig_min)
        {
            sig_min = min_temp;
        }

        if (event_status <= 0)
        {
            event_start_time = sys_time;
            event_status = 16;
        }
    }
}