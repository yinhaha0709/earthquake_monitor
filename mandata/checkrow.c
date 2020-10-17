#include <stdio.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include "../include/config.h"
#include "../include/checkrow.h"
#include "../include/database.h"

void * row_check(void * arg)
{
    MYSQL *mysql;
    int data_row_num_init = 0;

    mysql = mysql_init(NULL);           
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql);

    pthread_mutex_lock(&mutex_row_check);
    mysqldb_query(mysql, "count(*)", TABLE_NAME1, "1", "1");
    data_row_num_init = atoi(row[0]);

    mysqldb_update(mysql, MESSAGE_INT, data_row_num_init);
    printf("check row finish!\n");
    pthread_mutex_unlock(&mutex_row_check);
    close_connection(mysql);
}