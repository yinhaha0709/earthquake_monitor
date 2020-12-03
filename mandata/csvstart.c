#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "../include/systime.h"
#include "../include/config.h"
#include "../include/database.h"

void * csv_start()
{
    MYSQL *mysql_csv;

    event_start_time = sys_time;
    event_status = 16;

    get_date_time();

    mysql_csv = mysql_init(NULL);
    if (!mysql_csv)
    {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql_csv);
    mysqldb_query_csv(mysql_csv, "value1, value2, value3, value4, value5, value6", TABLE_NAME1, "1", "1 order by timestrap desc limit 3000");
    close_connection(mysql_csv);

    pthread_detach(pthread_self());
}