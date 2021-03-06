#include <stdio.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include "../include/config.h"
#include "../include/checkrow.h"
#include "../include/database.h"
#include "../include/systime.h"

//extern pthread_mutex_t mutex_row_check;

void * row_check()
{
    MYSQL *mysql;
    MYSQL_ROW row2;
    int data_row_num_init = 0, data_row_to_delete = 0;
    double check_time_temp = get_system_time3f();
    printf("check row start: %f\n", check_time_temp);

    mysql = mysql_init(NULL);           
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql);

    pthread_mutex_lock(&mutex_row_check);
    data_row_num_init = mysqldb_query_row(mysql, "count(*)", TABLE_NAME1, "1", "1");

    if((data_row_num_init - 24000) > 0){
        data_row_to_delete = data_row_num_init - 24000;
        mysqldb_delete(mysql, TABLE_NAME1, "timestrap asc", data_row_to_delete);
        data_row_num_init = 24000;
    }
    //printf("%d", data_row_num_init);

    mysqldb_update(mysql, MESSAGE_INT, data_row_num_init, 3);
    //printf("check row finish!\n");
    pthread_mutex_unlock(&mutex_row_check);
    close_connection(mysql);
    check_time_temp = get_system_time3f();
    printf("check row finish: %f\n", check_time_temp);
}