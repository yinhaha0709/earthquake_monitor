/*
    Contains functions that generate virtual signals.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include "../include/systime.h"
#include "../include/arrayop.h"
#include "../include/config.h"
#include "../include/database.h"
#include "../include/savdata.h"
#include "../include/checkrow.h"
#include "../include/datacharacteric.h"

//extern double **c;
pthread_mutex_t mutex, mutex_row_check, mutex_cal;

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
    int row_num;
    pthread_t id_t1, id_t2, id_t3;
    double a, point_per_sec, time_temp1, time_temp2, time_temp3, now_time3f;
    int b,  j, k, data_row_num_init;
    int simple_rate = SIMPLE_RATE;
    MYSQL *mysql1;
    //MYSQL_ROW row3;

//    pthread_mutex_t mutex, mutex_row_check;
 //   int sec = 10;
    double c[20];
    for(j=0; j<20; j++)
        c[j] = 0;
 /*   char str1[BUF_SIZE], str2[2400][10][BUF_SIZE];

    memset(str1, 0, BUF_SIZE);
    for(j=0; j<2400; j++)
        for(k=0; k<10; k++)
            memset(str2[j][k], 0, BUF_SIZE);
*/
    srand((int)time(0));

    b = rand()%1000000; 
    a = b / 1000000.0;
    //printf("%f", a);

    point_per_sec = 1.0/simple_rate;
    //printf("%f\n", point_per_sec);

    row_num = 0, j = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex_row_check, NULL);

    //time_temp1 = get_system_time3f();
    //printf("row in data start time: %f\n", time_temp1);
/*
    mysql1 = mysql_init(NULL);           
    if (!mysql1) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql1);
    pthread_mutex_lock(&mutex_row_check);
    row3 = mysqldb_query(mysql1, "count(*)", TABLE_NAME1, "1", "1");
    data_row_num_init = atoi(row3[0]);

    mysqldb_update(mysql1, MESSAGE_INT, data_row_num_init);
    pthread_mutex_unlock(&mutex_row_check);
    close_connection(mysql1);
*/
    row_check();
    
    time_temp1 = get_system_time3f();
    time_temp2 = time_temp1;
    time_temp3 = time_temp1 + 0.5;
    //printf("row in data finish time: %f\n", time_temp1);
    //printf("%d\n", row_num);

    while(1)
    {
        now_time3f = get_system_time3f();
        //printf("%d\n", row_num);
        if(row_num >= 10){
            row_num = 0;
            pthread_create(&id_t1, NULL, data_save, (void*)&c);
            //pthread_join(id_t1, NULL);
        }

        if((now_time3f - time_temp2) >= 1.0){
            //printf("while row check\n");
            pthread_create(&id_t2, NULL, row_check, NULL);
            time_temp2 = now_time3f;
        }

        if((now_time3f - time_temp3) >= 1.0){
            pthread_create(&id_t3, NULL, data_calculation_operation, NULL);
            time_temp3 = now_time3f;
        }

        if( (now_time3f - time_temp1) > -0.0001){
            pthread_mutex_lock(&mutex);
            c[row_num] = now_time3f;
            c[row_num + 10] = random_sig(a);
            a = c[row_num + 10];
            pthread_mutex_unlock(&mutex);
            //printf("%f %f\n", c[row_num], c[row_num + 10]);
            row_num++;
            //printf("row_num = %d", row_num);
            time_temp1 +=  point_per_sec;
            //printf("%f\n", time_temp1);
        } 

    }

    time_temp1 = get_system_time3f();
    printf("%f", time_temp1);
   // fclose(fp);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex_row_check);
    //free_memory_double(c, 10);
    return 0;
}