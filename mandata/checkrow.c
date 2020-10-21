#include <stdio.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include "../include/config.h"
#include "../include/checkrow.h"
#include "../include/database.h"

extern pthread_mutex_t mutex_row_check;

void * row_check()
{
    MYSQL *mysql;
    MYSQL_ROW row2;
    int data_row_num_init = 0;

    mysql = mysql_init(NULL);           
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql);

    pthread_mutex_lock(&mutex_row_check);
    row2 = mysqldb_query(mysql, "count(*)", TABLE_NAME1, "1", "1");

    data_row_num_init = atoi(row2[0]);
    //printf("%d", data_row_num_init);

    mysqldb_update(mysql, MESSAGE_INT, data_row_num_init);
    printf("check row finish!\n");
    pthread_mutex_unlock(&mutex_row_check);
    close_connection(mysql);
}