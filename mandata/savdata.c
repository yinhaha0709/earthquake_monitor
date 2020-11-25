#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
#include <pthread.h>
#include "../include/config.h"
#include "../include/savdata.h"
#include "../include/database.h"
#include "../include/systime.h"
#include "../include/arrayop.h"

//double **c;
//pthread_mutex_t mutex, mutex_row_check;
/*
void * data_save_test(void * arg)
{
    double runtime;
    int m = 0;
    int data_row_num = 0;    
    double **d = allocation_memory_double(100,2);
    MYSQL *mysql;
    MYSQL_ROW row2;

    runtime = get_system_time3f();
    printf("data save pthread start time: %f\n", runtime);

    pthread_mutex_lock(&mutex);
    //printf("mutex data ok");
    for(m=0; m<100; m++)
    {
        //d[m][0] = c[m][0];
        //d[m][1] = c[m][1];
        d[m][0] =((double*)arg)[m];
        d[m][1] = ((double*)arg)[m + 100];
        //printf("%f %f\n", d[m][0], d[m][1]);
    }
    //printf("copy data ok\n");
    pthread_mutex_unlock(&mutex);
    //printf("mutex data ok\n");

    mysql = mysql_init(NULL); 
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql);


    pthread_mutex_lock(&mutex_row_check);
    row2 = mysqldb_query_row(mysql, MESSAGE_INT, TABLE_NAME2, "id", "1");
    data_row_num = atoi(row2[0]);
    pthread_mutex_unlock(&mutex_row_check);

    if( data_row_num >= 24000){
        mysqldb_delete(mysql, TABLE_NAME1, "timestrap asc", 50);
    }
    else{
        data_row_num += 100;
        pthread_mutex_lock(&mutex_row_check);
        mysqldb_update(mysql, MESSAGE_INT, data_row_num);
        pthread_mutex_unlock(&mutex_row_check);
    } 

    for(m=0; m<100; m++)
    {
        mysqldb_insert(mysql, d[m][0], d[m][1]);
    }

    close_connection(mysql);

    //free_memory_double(d, 10);

    runtime = get_system_time3f();
    printf("data save pthread finish time: %f\n", runtime);
}
*/
void *data_save(void *arg)
{
    double runtime;
    int m = 0;
    int data_row_num = 0;
    double **d = allocation_memory_double(50, 7);
    char message[200] = {0};
    MYSQL *mysql;

    runtime = get_system_time3f();
    printf("data save pthread start time: %f\n", runtime);

    pthread_mutex_lock(&mutex);
    //printf("mutex data ok");
    for (m = 0; m < 50; m++)
    {
        //d[m][0] = c[m][0];
        //d[m][1] = c[m][1];
        d[m][0] = ((double *)arg)[m * 7];
        d[m][1] = ((double *)arg)[m * 7 + 1];
        d[m][2] = ((double *)arg)[m * 7 + 2];
        d[m][3] = ((double *)arg)[m * 7 + 3];
        d[m][4] = ((double *)arg)[m * 7 + 4];
        d[m][5] = ((double *)arg)[m * 7 + 5];
        d[m][6] = ((double *)arg)[m * 7 + 6];
        //printf("%f %f\n", d[m][0], d[m][1]);
    }
    printf("copy data ok\n");
    pthread_mutex_unlock(&mutex);
    //printf("mutex data ok\n");

    mysql = mysql_init(NULL);
    if (!mysql)
    {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql);

    for (m = 0; m < 50; m++)
    {
        sprintf(message, "%f, %f, %f, %f, %f, %f, %f", d[m][0], d[m][1], d[m][2], d[m][3], d[m][4], d[m][5], d[m][6]);
        mysqldb_insert(mysql, TABLE_NAME1, "timestrap, value1, value2, value3, value4, value5, value6", message);
        memset(message, 0, sizeof(message));
    }

    pthread_mutex_lock(&mutex_row_check);
    data_row_num = mysqldb_query_row(mysql, MESSAGE_INT, TABLE_NAME2, "id", "1");
    pthread_mutex_unlock(&mutex_row_check);

    if (data_row_num >= 24000)
    {
        mysqldb_delete(mysql, TABLE_NAME1, "timestrap asc", 50);
    }
    else
    {
        data_row_num += 50;
        pthread_mutex_lock(&mutex_row_check);
        mysqldb_update(mysql, MESSAGE_INT, data_row_num, 3);
        pthread_mutex_unlock(&mutex_row_check);
    }

    //free_memory_double(d, 10);

    close_connection(mysql);

    runtime = get_system_time3f();
    printf("data save pthread finish time: %f\n", runtime);
}
