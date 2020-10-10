/*      
    Get the system time.
    which can be accurate to seconds (for general events), 
    one decimal place (for triggering events), 
    or milliseconds (for sampling)
*/
#include <stdio.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include "systime.h"

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