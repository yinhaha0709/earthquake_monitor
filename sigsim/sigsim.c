/*
    Contains functions that generate virtual signals.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../include/systime.h"
#include "../include/arrayop.h"
#include "../include/config.h"
#include "../include/database.h"
#include "../include/savdata.h"
#include "../include/checkrow.h"

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
    pthread_t id_t1, id_t2;
    double a, point_per_sec, start_time, start_time1, now_time3f;
    int b,  j, k, data_row_num_init;
    MYSQL *mysql1;
 //   int sec = 10;


    c = allocation_memory_double(10, 2);

 //   double **d = allocation_memory_double(2400, 10);
    char str1[BUF_SIZE], str2[2400][10][BUF_SIZE];

    memset(str1, 0, BUF_SIZE);
    for(j=0; j<2400; j++)
        for(k=0; k<10; k++)
            memset(str2[j][k], 0, BUF_SIZE);

    srand((int)time(0));

    b = rand()%1000000;

    a = b / 1000000.0;
    //printf("%f", a);

    point_per_sec = 1.0/simple_rate;
    //printf("%f\n", point_per_sec);

    row_num = 0, j = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex_row_check, NULL);

    start_time = get_system_time3f();
    printf("row in data start time: %f\n", start_time);

    mysql1 = mysql_init(NULL);           
    if (!mysql1) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql1);
    pthread_mutex_lock(&mutex_row_check);
    mysqldb_query(mysql1, "count(*)", TABLE_NAME1, "1", "1");
    data_row_num_init = atoi(row[0]);

    mysqldb_update(mysql1, MESSAGE_INT, data_row_num_init);
    pthread_mutex_unlock(&mutex_row_check);
    close_connection(mysql1);
    
    start_time = get_system_time3f();
    start_time1 = start_time;
    printf("row in data finish time: %f\n", start_time);

    while(1)
    {
        now_time3f = get_system_time3f();
        //printf("%d\n", row_num);
        if(row_num >= 10){
            row_num = 0;
            pthread_create(&id_t1, NULL, data_save, NULL);
            //pthread_join(id_t1, NULL);
        }

        if( (now_time3f - start_time) > -0.0001){
            pthread_mutex_lock(&mutex);
            c[row_num][0] = now_time3f;
            c[row_num][1] = random_sig(a);
            a = c[row_num][1];
            pthread_mutex_unlock(&mutex);
            //printf("%f %f\n", c[row_num][1], c[row_num][2]);
            row_num++;
            start_time +=  point_per_sec;
            //printf("%f\n", start_time);
        } 

        if((now_time3f - start_time1) > 1.0){
            pthread_create(&id_t2, NULL, row_check, NULL);
            start_time1 = now_time3f;
        }
    }

    start_time = get_system_time3f();
    printf("%f", start_time);
   // fclose(fp);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex_row_check);
    free_memory_double(c, 10);
    return 0;
}