#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <mysql/mysql.h>
#include <mosquitto.h>
#include <unistd.h>
#include <pthread.h>
#include "../include/config.h"
#include "../include/mqtt.h"
#include "../include/infoinit.h"
#include "../include/register.h"
#include "../include/event.h"
#include "../include/database.h"
#include "../include/systime.h"

pthread_mutex_t mutex, mutex_row_check, mutex_cal, mutex_min, mutex_max, mutex_ave;
double sig_g[6];
double sys_time;
char station_id[8], mode, version;
float longitude, latitude, strain, acceleration;
short int simple_rate, simple_num;
char position_num[2], station_num[2];
char topic_regpub[30], topic_regsub[33], topic_feature[29], topic_ontimepub[28], topic_ontimesub[31], topic_event[27];
char threshold_status[6];
float earthquake_max, sig_max, sig_min;
int event_num;

int main(void)
{
    MYSQL *mysql1;

    pthread_t id_t1, id_t2;

    earthquake_max = 0;

   mysql1 = mysql_init(NULL);
    if (!mysql1)
    {
        printf("\nMysql init failed.\n");
    }

    //char value = 1;
    //mysql_options(&mysql1, MYSQL_OPT_RECONNECT, (char *)&value);

    mysqldb_connect(mysql1);

    ontime_status = mysqldb_query_row(mysql1, MESSAGE_INT, TABLE_NAME2, "id", "1");
    ftp_status = mysqldb_query_row(mysql1, MESSAGE_INT, TABLE_NAME2, "id", "2");
    event_num = mysqldb_query_row(mysql1, MESSAGE_INT, TABLE_NAME2, "id", "3");

    printf("%d, %d\n", ontime_status, ftp_status);
    close_connection(mysql1);
    mysql_library_end();

    information_init();
    register_send();

    sig_max = 0.059342;
    sig_min = -0.089231;
    sys_time = get_system_time3f();
    event_start_time = get_system_time3f();

    //earthquake_event();
    pthread_create(&id_t1, NULL, earthquake_event, NULL);

    sleep(3);
    sys_time = get_system_time3f();
    //earthquake_end();
    pthread_create(&id_t2, NULL, earthquake_end, NULL);

    while(1)
    {
        sleep(1);
        //earthquake_event();
    }
}

