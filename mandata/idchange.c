#include <stdio.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include "../include/config.h"
#include "../include/database.h"
#include "../include/systime.h"
#include "../include/idchange.h"

void * id_change()
{
    //MYSQL *mysql;
    MYSQL *mysql_id;
    double check_time_temp = get_system_time3f();
    printf("check row start: %f\n", check_time_temp);
/*
    mysql_id = mysql_init(NULL);           
    if (!mysql_id) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql_id);
*/
    mysql_id = mysql_init(NULL);           
    if (!mysql_id) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql_id);

    pthread_mutex_lock(&mutex_min);
    mysqldb_alter(mysql_id, TABLE_NAME3, "id");
    pthread_mutex_unlock(&mutex_min);

    pthread_mutex_lock(&mutex_max);
    mysqldb_alter(mysql_id, TABLE_NAME4, "id");
    pthread_mutex_unlock(&mutex_max);

    pthread_mutex_lock(&mutex_ave);
    mysqldb_alter(mysql_id, TABLE_NAME5, "id");
    pthread_mutex_unlock(&mutex_ave);
    
    close_connection(mysql_id);
    //mysql_library_end();

    check_time_temp = get_system_time3f();
    printf("check row finish: %f\n", check_time_temp);

    pthread_detach(pthread_self());
}