#include <stdio.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include "../include/config.h"
#include "../include/database.h"
#include "../include/systime.h"
#include "../include/idchange.h"

void * id_change()
{
    MYSQL *mysql;
    double check_time_temp = get_system_time3f();
    printf("check row start: %f\n", check_time_temp);
/*
    mysql = mysql_init(NULL);           
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql);
*/
    pthread_mutex_lock(&mutex_min);
    mysqldb_alter(mysql, TABLE_NAME3, "id");
    pthread_mutex_unlock(&mutex_min);

    pthread_mutex_lock(&mutex_max);
    mysqldb_alter(mysql, TABLE_NAME4, "id");
    pthread_mutex_unlock(&mutex_max);

    pthread_mutex_lock(&mutex_ave);
    mysqldb_alter(mysql, TABLE_NAME5, "id");
    pthread_mutex_unlock(&mutex_ave);
    
    //close_connection(mysql);

    check_time_temp = get_system_time3f();
    printf("check row finish: %f\n", check_time_temp);
}