#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/systime.h"
#include "../include/config.h"

int main(void)
{
    FILE *fp_test;
    //time_t rawtime;
    //char *str;
    //struct tm * timeinfo;
    int i;
    char test_data[1024], test_name[1024], test_script[1024];
    //double timestrap;
    double d[3][6] = {0.343454, 0.232323, 0.023412, 0.343454, 0.232323, 0.023412, 0.234222, 0.234221, 0.231112, 0.234222, 0.234221, 0.231112, 0.343454, 0.232323, 0.023412, 0.234222, 0.234221, 0.231112};
/*
    time(&rawtime);
    timeinfo = localtime(&rawtime);
*/    
    //printf("%d, %d, %d, %d, %d, %d\n", timeinfo->tm_year % 100, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
/*
    int eq_year, eq_month, eq_day, eq_hour, eq_min, eq_sec;

    eq_year = timeinfo->tm_year % 100;
    eq_month = timeinfo->tm_mon + 1;
    eq_day = timeinfo->tm_mday;
    eq_hour = timeinfo->tm_hour;
    eq_min = timeinfo->tm_min;
    eq_sec = timeinfo->tm_sec;
*/
    get_date_time();
    float test_max = 0.013073, test_min = -0.020829;

    sprintf(test_data, "Burst_%02d%02d%02d%02d%02d%02d_%.3f_%.3f.csv", eq_year, eq_month, eq_day, eq_hour, eq_min, eq_sec, test_max * 1000, test_min * 1000);
    sprintf(test_name, "../data/%s", test_data);
    sprintf(test_script, "./../ftp_send/ftp_send.sh %s &", test_data);
    printf("%s, %s, %s\n", test_data, test_name, test_script);
    

    fp_test = fopen("../data/test1.csv", "a+");
    //fwrite(test_data, strlen(test_data), 1, fp_test);
    for(i=0; i<3; i++)
    {
        fprintf(fp_test, "%f\t%f\t%f\t%f\t%f\t%f\n", d[i][0], d[i][1], d[i][2], d[i][3], d[i][4], d[i][5]);
    }
    fclose(fp_test);
    
    rename("../data/test1.csv", test_name);
    system(test_script);
    printf("success\n");

    return 0;
}