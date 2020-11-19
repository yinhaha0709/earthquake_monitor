#include <stdio.h>
#include <math.h>
#include "../include/config.h"
#include "../include/searchmax.h"
#include "../include/getstatus.h"

float get_status(double a[], int num, float nominal)
{
    int i = 0;
    //double sensor_status = 0;
    double difference[ num-1 ];
    double diff_max;

    for(i=0; i<num-1; i++)
        difference[ i ] = a[ i+1 ] - a[ i ];

    for(i=0; i<num-2; i++)
    {
        if(difference[ i ] != (-difference[i+1])){
            break;
        }
        if(i == num-3){
            return 3.0;
        }
    }

    for(i=0; i<num-1; i++){
        if((difference[i] = fabs(difference[i])) < 0.001)
            break;

        if(i == num-2)
            return 0;
    }

    if((nominal - search_max(difference, num-1)) < 0.001)
        return 1.0;
    else
        return 2.0;
}