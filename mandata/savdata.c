#include <stdio.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include "../include/config.h"
#include "../include/savdata.h"
#include "../include/database.h"
#include "../include/systime.h"
#include "../include/arrayop.h"

extern double **c;
extern pthread_mutex_t mutex, mutex_row_check;

void * data_save(void * arg)
{
    double runtime;
    int m = 0;
    int data_row_num = 0;    
    double **d = allocation_memory_double(10,2);
    MYSQL *mysql;
    MYSQL_ROW row2;

    runtime = get_system_time3f();
    printf("data save pthread start time: %f\n", runtime);

    mysql = mysql_init(NULL);           
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }
    mysqldb_connect(mysql);

    pthread_mutex_lock(&mutex);
    for(m=0; m<10; m++)
    {
        d[m][0] = c[m][0];
        d[m][1] = c[m][1];
    }
    pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&mutex_row_check);
    row2 = mysqldb_query(mysql, MESSAGE_INT, TABLE_NAME2, "id", "1");
    data_row_num = atoi(row2[0]);
    pthread_mutex_unlock(&mutex_row_check);

    if( data_row_num >= 24000){
        mysqldb_delete(mysql, "data_test", "timestrap", "10");
    }
    else{
        data_row_num += 10;
        pthread_mutex_lock(&mutex_row_check);
        mysqldb_update(mysql, MESSAGE_INT, data_row_num);
        pthread_mutex_unlock(&mutex_row_check);
    } 

    for(m=0; m<10; m++)
    {
        mysqldb_insert(mysql, d[m][0], d[m][1]);
    }

    close_connection(mysql);

    runtime = get_system_time3f();
    printf("data save pthread finish time: %f\n", runtime);
}