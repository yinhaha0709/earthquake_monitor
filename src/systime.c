/*      
    Get the system time.
    which can be accurate to seconds (for general events), 
    one decimal place (for triggering events), 
    or milliseconds (for sampling)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <time.h>
#include "../include/systime.h"

int eq_year, eq_month, eq_day, eq_hour, eq_min, eq_sec;

//Get the system time, accurate to seconds
double get_system_time()
{
    struct timeb nowtime;
    double t;
    ftime(&nowtime);
    t = nowtime.time;
    return t;
}

//Get the system time, accurate to one decimal place
double get_system_time1f()
{
    struct timeb nowtime;
    int temp_decimal_time;
    long long temp_integer_time;
    double t;
    ftime(&nowtime);
    temp_integer_time = (1000 * nowtime.time + nowtime.millitm)/100;
    temp_decimal_time = (1000 * nowtime.time + nowtime.millitm)%100;
    if(temp_decimal_time >= 50){
        temp_integer_time += 1;
    }

    t = temp_integer_time /10.0;

    return t;
}

//Get the system time, accurate to milliseconds
double get_system_time3f()
{
    struct timeb nowtime;
    double t;
    ftime(&nowtime);
    t = (nowtime.time * 1000 + nowtime.millitm)/1000.0;
    return t;
}

void get_date_time()
{
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    eq_year = timeinfo->tm_year % 100;
    eq_month = timeinfo->tm_mon + 1;
    eq_day = timeinfo->tm_mday;
    eq_hour = timeinfo->tm_hour;
    eq_min = timeinfo->tm_min;
    eq_sec = timeinfo->tm_sec;

}