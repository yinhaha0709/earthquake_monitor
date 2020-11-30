#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include "../include/config.h"
#include "../include/database.h"
#include "../include/searchaverage.h"
#include "../include/searchmax.h"
#include "../include/searchmin.h"
#include "../include/getstatus.h"
#include "../include/systime.h"
#include "../include/mqtt.h"
#include "../include/commfeature.h"

float min_1s[6], max_1s[6], min_5s[6], max_5s[6], min_30s[6], max_30s[6], ave_3s[6], ave_60s[6], ave_ratio[6], sensor_status[6];
char message1[100], message2[100], message3[100];

void *feature_change(void *arg)
{
    //pthread_mutex_t mutex_change;
    //MYSQL *mysql;
    int row = 0;
    int row_temp;
    int x, y;
    char *table_name = (char *)arg;

    printf("%s\n", table_name);
    /*
    mysql = mysql_init(NULL);
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }
    mysqldb_connect(mysql);
*/
    if (strcmp(table_name, TABLE_NAME3) == 0)
    {
        double min_array[6][30];
        MYSQL *mysql_min;

        mysql_min = mysql_init(NULL);
        if (!mysql_min)
        {
            printf("\nMysql init failed.\n");
        }
        mysqldb_connect(mysql_min);

        pthread_mutex_lock(&mutex_min);

        mysqldb_insert(mysql_min, TABLE_NAME3, "min_data_value1, min_data_value2, min_data_value3, min_data_value4, min_data_value5, min_data_value6", message1);
        row = mysqldb_query(mysql_min, "min_data_value1, min_data_value2, min_data_value3, min_data_value4, min_data_value5, min_data_value6", TABLE_NAME3, "1", "1 order by id desc");

        if (row > 30)
        {
            mysqldb_delete(mysql_min, TABLE_NAME3, "id asc", row - 30);
            //mysqldb_alter(mysql, TABLE_NAME3, "id");
            row = 30;
        }

        for (x = 0; x < 6; x++)
            for (y = 0; y < row; y++)
            {
                min_array[x][y] = min_check_array[x][y];
                //printf("%f\n", min_array[x][y]);
            }

        for (x = 0; x < 6; x++)
        {
            min_1s[x] = min_array[x][0];
        }

        if (row < 5)
        {
            for (x = 0; x < 6; x++)
            {
                min_5s[x] = search_min(min_array[x], row);
                min_30s[x] = min_5s[x];
            }
        }
        else if (row < 30)
        {
            for (x = 0; x < 6; x++)
            {
                min_5s[x] = search_min(min_array[x], 5);
                min_30s[x] = search_min(min_array[x], row);
            }
        }
        else if (row >= 30)
        {
            for (x = 0; x < 6; x++)
            {
                min_5s[x] = search_min(min_array[x], 5);
                min_30s[x] = search_min(min_array[x], 30);
            }
        }

        pthread_mutex_unlock(&mutex_min);

        close_connection(mysql_min);
        //mysql_library_end();
    }

    if (strcmp(table_name, TABLE_NAME4) == 0)
    {
        double max_array[6][30];
        MYSQL *mysql_max;

        mysql_max = mysql_init(NULL);
        if (!mysql_max)
        {
            printf("\nMysql init failed.\n");
        }
        mysqldb_connect(mysql_max);

        pthread_mutex_lock(&mutex_max);

        mysqldb_insert(mysql_max, TABLE_NAME4, "max_data_value1, max_data_value2, max_data_value3, max_data_value4, max_data_value5, max_data_value6", message2);

        row = mysqldb_query(mysql_max, "max_data_value1, max_data_value2, max_data_value3, max_data_value4, max_data_value5, max_data_value6", TABLE_NAME4, "1", "1 order by id desc");

        if (row > 30)
        {
            mysqldb_delete(mysql_max, TABLE_NAME4, "id asc", row - 30);
            //mysqldb_alter(mysql, TABLE_NAME4, "id");
            row = 30;
        }

        for (x = 0; x < 6; x++)
            for (y = 0; y < row; y++)
            {
                max_array[x][y] = max_check_array[x][y];
                //printf("%f\n", min_array[x][y]);
            }

        for (x = 0; x < 6; x++)
        {
            max_1s[x] = max_array[x][0];
        }

        if (row < 5)
        {
            for (x = 0; x < 6; x++)
            {
                max_5s[x] = search_max(max_array[x], row);
                max_30s[x] = max_5s[x];
            }
        }
        else if (row < 30)
        {
            for (x = 0; x < 6; x++)
            {
                max_5s[x] = search_max(max_array[x], 5);
                max_30s[x] = search_max(max_array[x], row);
            }
        }
        else if (row >= 30)
        {
            for (x = 0; x < 6; x++)
            {
                max_5s[x] = search_max(max_array[x], 5);
                max_30s[x] = search_max(max_array[x], 30);
            }
        }

        pthread_mutex_unlock(&mutex_max);

        close_connection(mysql_max);
        //mysql_library_end();
    }

    if (strcmp(table_name, TABLE_NAME5) == 0)
    {
        double ave_array[6][60];

        MYSQL *mysql_ave;

        mysql_ave = mysql_init(NULL);
        if (!mysql_ave)
        {
            printf("\nMysql init failed.\n");
        }
        mysqldb_connect(mysql_ave);

        pthread_mutex_lock(&mutex_ave);

        mysqldb_insert(mysql_ave, TABLE_NAME5, "ave_data_value1, ave_data_value2, ave_data_value3, ave_data_value4, ave_data_value5, ave_data_value6", message3);
        row = mysqldb_query(mysql_ave, "ave_data_value1, ave_data_value2, ave_data_value3, ave_data_value4, ave_data_value5, ave_data_value6", TABLE_NAME5, "1", "1 order by id desc");

        if (row > 60)
        {
            mysqldb_delete(mysql_ave, TABLE_NAME5, "id asc", row - 60);
            //mysqldb_alter(mysql, TABLE_NAME5, "id");
            row = 60;
        }

        for (x = 0; x < 6; x++)
            for (y = 0; y < row; y++)
            {
                ave_array[x][y] = ave_check_array[x][y];
                //printf("%f\n", min_array[x][y]);
            }

        if (row < 3)
        {
            for (x = 0; x < 6; x++)
            {
                ave_3s[x] = search_average(ave_array[x], row);
                ave_60s[x] = ave_3s[x];
            }
        }
        else if (row < 60)
        {
            for (x = 0; x < 6; x++)
            {
                ave_3s[x] = search_average(ave_array[x], 3);
                ave_60s[x] = search_average(ave_array[x], row);
            }
        }
        else if (row >= 60)
        {
            for (x = 0; x < 6; x++)
            {
                ave_3s[x] = search_average(ave_array[x], 3);
                ave_60s[x] = search_average(ave_array[x], 60);
            }
        }

        for (x = 0; x < 6; x++)
        {
            if (ave_3s[x] == 0.0)
                ave_ratio[x] = 0;
            else
                ave_ratio[x] = ave_60s[x] / ave_3s[x];
        }

        pthread_mutex_unlock(&mutex_ave);

        close_connection(mysql_ave);
        //mysql_library_end();
    }

    //close_connection(mysql);
    //pthread_detach(pthread_self());
}

void *feature_send(void *arg)
{
    char *type = "fd";
    char endian = ENDIAN;
    char num, num_next, tunnel;
    int data_long = 311;
    int block_long = 48;
    uint8_t payload[311];
    memset(payload, 0, 311);
    int i, j;
    double t1 = *(double *)arg;

    memcpy(&payload[0], type, 2);
    memcpy(&payload[2], &data_long, 4);
    memcpy(&payload[6], station_id, 8);
    memcpy(&payload[14], &t1, 8);
    memcpy(&payload[22], &mode, 1);
    i = 23, j = 0;
    for (j = 0; j < 6; j++)
    {
        num = j + 1;
        num_next = j + 2;
        if (j >= 5)
            num_next = 0;
        tunnel = num;

        memcpy(&payload[i], &num, 1);
        memcpy(&payload[i + 1], &num_next, 1);
        memcpy(&payload[i + 2], &endian, 1);
        memcpy(&payload[i + 3], &block_long, 4);
        memcpy(&payload[i + 7], &tunnel, 1);
        memcpy(&payload[i + 8], &max_1s[j], 4);
        memcpy(&payload[i + 12], &min_1s[j], 4);
        memcpy(&payload[i + 16], &max_5s[j], 4);
        memcpy(&payload[i + 20], &min_5s[j], 4);
        memcpy(&payload[i + 24], &max_30s[j], 4);
        memcpy(&payload[i + 28], &min_30s[j], 4);
        memcpy(&payload[i + 32], &ave_3s[j], 4);
        memcpy(&payload[i + 36], &ave_60s[j], 4);
        memcpy(&payload[i + 40], &ave_ratio[j], 4);
        memcpy(&payload[i + 44], &sensor_status[j], 4);

        i = i + 48;
    }
    /*
    for(i = 0; i < data_long; i++)
    {
        printf("%x ", payload[i]);
    }
*/
    printf("feature send ok !");

    vibration_publish(topic_feature, payload, data_long);
    //pthread_detach(pthread_self());
}

void *common_feature()
{
    //MYSQL *mysql;
    MYSQL *mysql_common;
    double e[6][200], max[6], min[6], ave[6], time_temp4;
    int row = 0, i = 0, row_send = 0;
    float nominal;
    pthread_t id_min, id_max, id_ave, id_featsend;
    char *min_table = TABLE_NAME3;
    char *max_table = TABLE_NAME4;
    char *ave_table = TABLE_NAME5;
    char field_message[1024], value_message[2048];
    double t;

    t = get_system_time();

    time_temp4 = get_system_time3f();
    printf("\ndata cal start time: %f\n", time_temp4);
    /*
    //pthread_mutex_lock(&mutex_cal);
    mysql = mysql_init(NULL);
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }
    mysqldb_connect(mysql);
*/

    mysql_common = mysql_init(NULL);
    if (!mysql_common)
    {
        printf("\nMysql init failed.\n");
    }
    mysqldb_connect(mysql_common);

    mysqldb_query(mysql_common, "value1, value2, value3, value4, value5, value6", TABLE_NAME1, "1", "1 order by timestrap desc limit 200");

    for (row = 0; row < 6; row++)
        for (i = 0; i < 200; i++)
        {
            e[row][i] = data_check_array[row][i];
            //printf("%f\n", e[i]);
        }

    for (row = 0; row < 6; row++)
    {
        max[row] = search_max(e[row], 200);
        min[row] = search_min(e[row], 200);
        ave[row] = search_average(e[row], 200);
        if (row < 3)
            nominal = acceleration;
        else
            nominal = strain;

        sensor_status[row] = get_status(e[row], 200, nominal);
    }

    memset(message1, 0, 100);
    memset(message2, 0, 100);
    memset(message3, 0, 100);

    sprintf(message1, "%f, %f, %f, %f, %f, %f", min[0], min[1], min[2], min[3], min[4], min[5]);
    sprintf(message2, "%f, %f, %f, %f, %f, %f", max[0], max[1], max[2], max[3], max[4], max[5]);
    sprintf(message3, "%f, %f, %f, %f, %f, %f", ave[0], ave[1], ave[2], ave[3], ave[4], ave[5]);

    pthread_create(&id_min, NULL, feature_change, (void *)min_table);
    pthread_create(&id_max, NULL, feature_change, (void *)max_table);
    pthread_create(&id_ave, NULL, feature_change, (void *)ave_table);

    pthread_join(id_min, NULL);
    pthread_join(id_max, NULL);
    pthread_join(id_ave, NULL);

    pthread_create(&id_featsend, NULL, feature_send, (void *)&t);

    strcpy(field_message, "timestrap, max_value1_1s, min_value1_1s, \
max_value1_5s, min_value1_5s, max_value1_30s, min_value1_30s,\
ave_value1_3s, ave_value1_60s, ave_ratio1, sensor_status1, \
max_value2_1s, min_value2_1s, max_value2_5s, min_value2_5s, \
max_value2_30s, min_value2_30s, ave_value2_3s, ave_value2_60s, ave_ratio2, sensor_status2, \
max_value3_1s, min_value3_1s, max_value3_5s, min_value3_5s, \
max_value3_30s, min_value3_30s, ave_value3_3s, ave_value3_60s, ave_ratio3, sensor_status3, \
max_value4_1s, min_value4_1s, max_value4_5s, min_value4_5s, max_value4_30s, min_value4_30s, \
ave_value4_3s, ave_value4_60s, ave_ratio4, sensor_status4, \
max_value5_1s, min_value5_1s, max_value5_5s, min_value5_5s, max_value5_30s, min_value5_30s, \
ave_value5_3s, ave_value5_60s, ave_ratio5, sensor_status5, \
max_value6_1s, min_value6_1s, max_value6_5s, min_value6_5s, max_value6_30s, min_value6_30s, \
ave_value6_3s, ave_value6_60s, ave_ratio6, sensor_status6");

    sprintf(value_message, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, \
%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, \
%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f",
            t, max_1s[0], min_1s[0], max_5s[0], min_5s[0], max_30s[0], min_30s[0], ave_3s[0], ave_60s[0], ave_ratio[0], sensor_status[0],
            max_1s[1], min_1s[1], max_5s[1], min_5s[1], max_30s[1], min_30s[1], ave_3s[1], ave_60s[1], ave_ratio[1], sensor_status[1],
            max_1s[2], min_1s[2], max_5s[2], min_5s[2], max_30s[2], min_30s[2], ave_3s[2], ave_60s[2], ave_ratio[2], sensor_status[2],
            max_1s[3], min_1s[3], max_5s[3], min_5s[3], max_30s[3], min_30s[3], ave_3s[3], ave_60s[3], ave_ratio[3], sensor_status[3],
            max_1s[4], min_1s[4], max_5s[4], min_5s[4], max_30s[4], min_30s[4], ave_3s[4], ave_60s[4], ave_ratio[4], sensor_status[4],
            max_1s[5], min_1s[5], max_5s[5], min_5s[5], max_30s[5], min_30s[5], ave_3s[5], ave_60s[5], ave_ratio[5], sensor_status[5]);
    //printf("\n%s\n%s\n", field_message, value_message);

    pthread_mutex_lock(&mutex_cal);
    mysqldb_insert(mysql_common, TABLE_NAME6, field_message, value_message);

    row_send = mysqldb_query_row(mysql_common, "count(*)", TABLE_NAME6, "1", "1");

    if (row_send >= 300)
        mysqldb_delete(mysql_common, TABLE_NAME6, "timestrap asc", row_send - 300);

    pthread_mutex_unlock(&mutex_cal);
    close_connection(mysql_common);
    //mysql_library_end();

    time_temp4 = get_system_time3f();
    printf("\ndata cal finish time: %f\n", time_temp4);
    pthread_join(id_featsend, NULL);
    pthread_detach(pthread_self());
}
