#include <stdio.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include "../include/config.h"
#include "../include/database.h"
#include "../include/systime.h"
#include "../include/rowchange.h"

//extern pthread_mutex_t mutex_row_check;

void * row_change()
{
    //MYSQL *mysql;
    MYSQL *mysql_row;
    int data_row_num_init = 0, data_row_to_delete = 0;

    double check_time_temp = get_system_time3f();
    printf("check row start: %f\n", check_time_temp);
/*
    mysql = mysql_init(NULL);           
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql);
*/

    mysql_row = mysql_init(NULL);           
    if (!mysql_row) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql_row);   

    pthread_mutex_lock(&mutex_row_check);
    data_row_num_init = mysqldb_query_row(mysql_row, "count(*)", TABLE_NAME1, "1", "1");

    if((data_row_num_init - 24000) > 0){
        data_row_to_delete = data_row_num_init - 24000;
        mysqldb_delete(mysql_row, TABLE_NAME1, "timestrap asc", data_row_to_delete);
        //data_row_num_init = 24000;
    }
    printf("\n%d\n", data_row_num_init);

    //mysqldb_update(mysql, MESSAGE_INT, data_row_num_init);
    //printf("check row finish!\n");
    pthread_mutex_unlock(&mutex_row_check);

    close_connection(mysql_row);
    //mysql_library_end();
    
    check_time_temp = get_system_time3f();
    printf("check row finish: %f\n", check_time_temp);

    pthread_detach(pthread_self());
}