/*
    Contains functions that generate virtual signals.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "systime.h"
#include "arrayop.h"

//Generating virtual signals
double random_sig(double a)
{
    int x_range, x_min, z;
    double z_out = 0.0;
    double y_min = a - 0.2;
    x_range = 400000;
    x_min = y_min * 1000000;

    z = rand() % x_range + x_min;
    if(z >1000000){
        z = 999999;
    }
    else if(z < -1000000){
        z = -999999;
    }
    z_out = z /1000000.0;
    return z_out;
}

//Main function of generating virtual signal according to time
int main(int argc, char* argv[])
{
    double a, point_per_sec, start_time, now_time3f;
    int b, i, j;
    int sec = 10;
    int simple_rate = 200;
    double **c = allocation_memory_double(sec, simple_rate);

    srand((int)time(0));

    b = rand()%1000000;

    a = b / 1000000.0;
    //printf("%f", a);

    FILE *fp = NULL;
    fp = fopen("/home/zncg/data/wav_data1.txt", "w+");

    if(fp == NULL){
        printf("file open error!");
        return 0;
    }

    point_per_sec = 1.0/simple_rate;
    //printf("%f\n", point_per_sec);

    i = 0, j = 0;
    
    start_time = get_system_time3f();
    printf("%f", start_time);

    while(i < sec)
    {
        if(j  >= simple_rate){
            i++;
            j = 0;
        }

        now_time3f = get_system_time3f();
        if( (now_time3f - start_time) > -0.0001){
            c[i][j] = random_sig(a);
            a = c[i][j];
            fprintf(fp, "%f %f\n", now_time3f, c[i][j]);
            //printf("%f %f\n", start_time, c[i][j]);
            j++;
            start_time +=  point_per_sec;
            //printf("%f\n", start_time);
        }  
    }

    start_time = get_system_time3f();
    printf("%f", start_time);
    fclose(fp);

    free_memory_double(c, sec);
    return 0;
}