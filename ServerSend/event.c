#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <mysql/mysql.h>
#include "../include/config.h"
#include "../include/event.h"
#include "../include/mqtt.h"
#include "../include/database.h"

double event_start_time, event_time;
int earthquake_status, event_status;
float earthquake_max, earthquake_min, earthquake_range;
int event_num;

void *earthquake_event()
{
    char type[2] = "ti";
    char payload[39];
    int event_long = 39;
    int i;

    if (sig_max > earthquake_max)
    {
        earthquake_max = sig_max;
    }

    if (sig_min < earthquake_min)
    {
        earthquake_min = sig_min;
    }

    float Y;
    if (fabs(sig_min) > fabs(sig_max))
    {
        Y = (float)1000 * fabs(sig_min);
    }
    else
    {
        Y = (float)1000 * fabs(sig_max);
    }

    if (Y > earthquake_range)
    {
        earthquake_range = Y;
    }

    char intensity = 0;

    if (Y >= 20 && Y <= 25)
        intensity = 4;
    else if (Y > 25 && Y <= 50)
        intensity = 5;
    else if (Y > 50 && Y <= 100)
        intensity = 6;
    else if (Y > 100 && Y <= 200)
        intensity = 7;
    else if (Y > 200 && Y <= 350)
        intensity = 8;
    else if (Y > 350)
        intensity = 9;
    else
        intensity = 0;

    printf("%f %d %f %x %f\n", sys_time, event_num, event_start_time, intensity, earthquake_range);

    //event_num = 15;

    memcpy(&payload[0], type, 2);
    memcpy(&payload[2], &event_long, 4);
    memcpy(&payload[6], station_id, 8);
    memcpy(&payload[14], &sys_time, 8);
    memcpy(&payload[22], &event_num, 4);
    memcpy(&payload[26], &event_start_time, 8);
    memcpy(&payload[34], &intensity, 1);
    memcpy(&payload[35], &earthquake_range, 4);

    for (i = 0; i < 39; i++)
    {
        printf("%#x ", payload[i]);
    }

    vibration_publish(topic_event, payload, event_long);

    earthquake_status = 0;
    sig_max = -5;
    sig_min = 5;

    pthread_detach(pthread_self());
}

void *earthquake_end()
{
    char type[2] = "ti";
    char payload[39];
    int event_long = 39;
    int i;
    MYSQL *mysql_event_end;

    char intensity = 0;
    earthquake_range = 0;

    printf("%f %d %f %x %f\n", sys_time, event_num, event_start_time, intensity, earthquake_range);

    memcpy(&payload[0], type, 2);
    memcpy(&payload[2], &event_long, 4);
    memcpy(&payload[6], station_id, 8);
    memcpy(&payload[14], &sys_time, 8);
    memcpy(&payload[22], &event_num, 4);
    memcpy(&payload[26], &event_start_time, 8);
    memcpy(&payload[34], &intensity, 1);
    memcpy(&payload[35], &earthquake_range, 4);

    for (i = 0; i < 39; i++)
    {
        printf("%#x ", payload[i]);
    }

    vibration_publish(topic_event, payload, event_long);

    earthquake_max = -5.0;
    earthquake_min = 5.0;
    event_start_time = 0.0;
    earthquake_status = 0, event_status = 0;

    sig_max = -5.0;
    sig_min = 5.0;

    event_num++;

    //printf("finish\n");
    mysql_event_end = mysql_init(NULL);
    if (!mysql_event_end)
    {
        printf("\nMysql init failed.\n");
    }
    mysqldb_connect(mysql_event_end);
    mysqldb_update(mysql_event_end, MESSAGE_INT, event_num, 3);
    close_connection(mysql_event_end);

    pthread_detach(pthread_self());
}