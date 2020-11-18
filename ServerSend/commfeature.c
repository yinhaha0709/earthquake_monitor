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
#include "../include/systime.h"
#include "../include/cJSON.h"
#include "../include/mqtt.h"
#include "../include/generalSend.h"

float min_1s[6], max_1s[6], min_5s[6], max_5s[6], min_30s[6], max_30s[6], ave_3s[6], ave_60s[6], ave_ratio[6];
float sensor_status = SENSOR_STATUS;
double timestrap;

void common_feature_cal(int i, int j, int k, double t)
{
    pthread_t id_t5;
    MYSQL *mysql;
    double min_array[6][30], max_array[6][30], ave_array[6][60];
    //float min_1s[6], max_1s[6], min_5s[6], max_5s[6], min_30s[6], max_30s[6], ave_3s[6], ave_60s[6], ave_ratio[6];
    //float sensor_status = SENSOR_STATUS;
    int x = 0, y=0;
    char field_message[1024], value_message[2048];
    char tunnel = TUNNEL;

    mysql = mysql_init(NULL);
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }
    mysqldb_connect(mysql);

    printf("data_cal_change start\n");
    //pthread_mutex_lock(&mutex_min);
    mysqldb_query(mysql, "min_data_value1, min_data_value2, min_data_value3, min_data_value4, min_data_value5, min_data_value6", TABLE_NAME3, "1", "1 order by id desc limit 30");
    printf("query finish\n");
    for(x=0; x<6; x++)
    for(y=0; y<i; y++)
    {
        min_array[x][y] = min_check_array[x][y];
	//printf("%f\n", min_array[x][y]);
    }
    //pthread_mutex_unlock(&mutex_min);

    //pthread_mutex_lock(&mutex_max);
    mysqldb_query(mysql, "max_data_value1, max_data_value2, max_data_value3, max_data_value4, max_data_value5, max_data_value6", TABLE_NAME4, "1", "1 order by id desc limit 30");
    for(x=0; x<6; x++)
    for(y=0; y<j; y++)
        max_array[x][y] = max_check_array[x][y];
    //pthread_mutex_unlock(&mutex_max);

    //pthread_mutex_lock(&mutex_ave);
    mysqldb_query(mysql, "ave_data_value1, ave_data_value2, ave_data_value3, ave_data_value4, ave_data_value5, ave_data_value6", TABLE_NAME5, "1", "1 order by id desc limit 60");
    for(x=0; x<6; x++)
    for(y=0; y<k; y++)
        ave_array[x][y] = ave_check_array[x][y];
    //pthread_mutex_unlock(&mutex_ave);

    for(x=0; x<6; x++)
    {
        min_1s[x] = min_array[x][0];
        max_1s[x] = max_array[x][0];
    }


    if(i < 5){
        for(x=0; x<6; x++)
        {
            min_5s[x] = search_min(min_array[x], i);
            min_30s[x] = min_5s[x];
        }
    }
    else if(i < 30){
        for(x=0; x<6; x++)
        {
            min_5s[x] = search_min(min_array[x], 5);
            min_30s[x] = search_min(min_array[x], i);
        }
    }
    else if(i >= 30){
        for(x=0; x<6; x++)
        {
            min_5s[x] = search_min(min_array[x], 5);
            min_30s[x] = search_min(min_array[x], 30);
        }
    }

    if(j < 5){
        for(x=0; x<6; x++)
        {
            max_5s[x] = search_max(max_array[x], i);
            max_30s[x] = max_5s[x];
        }
    }
    else if(j < 30){
        for(x=0; x<6; x++)
        {
            max_5s[x] = search_max(max_array[x], 5);
            max_30s[x] = search_max(max_array[x], i);
        }
    }
    else if(j >= 30){
        for(x=0; x<6; x++)
        {
            max_5s[x] = search_max(max_array[x], 5);
            max_30s[x] = search_max(max_array[x], 30);
        }
    }

    if(k < 3){
        for(x=0; x<6; x++)
        {
            ave_3s[x] = search_average(ave_array[x], k);
            ave_60s[x] = ave_3s[x];
        }
    }
    else if(k < 60){
        for(x=0; x<6; x++)
        {
            ave_3s[x] = search_average(ave_array[x], 3);
            ave_60s[x] = search_average(ave_array[x], k);
        }
    }
    else if(k >= 60){
        for(x=0; x<6; x++)
        {
            ave_3s[x] = search_average(ave_array[x], 3);
            ave_60s[x] = search_average(ave_array[x], 60);
        }
    }

    for(x=0; x<6; x++)
    {
        if(ave_3s[x] == 0.0)
            ave_ratio[x] = 0;
        else
            ave_ratio[x] = ave_60s[x] / ave_3s[x];
    }

    //printf("\n%f: %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", t, max_1s[0], min_1s[0], max_5s[0], min_5s[0], max_30s[0], min_30s[0], ave_3s[0], ave_60s[0], ave_ratio[0], sensor_status);
    
    timestrap = t;

    pthread_create(&id_t5, NULL, generalFeature_Send, NULL);

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
%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f", \
    t, max_1s[0], min_1s[0], max_5s[0], min_5s[0], max_30s[0], min_30s[0], ave_3s[0], ave_60s[0], ave_ratio[0], sensor_status, \
    max_1s[1], min_1s[1], max_5s[1], min_5s[1], max_30s[1], min_30s[1], ave_3s[1], ave_60s[1], ave_ratio[1], sensor_status, \
    max_1s[2], min_1s[2], max_5s[2], min_5s[2], max_30s[2], min_30s[2], ave_3s[2], ave_60s[2], ave_ratio[2], sensor_status, \
    max_1s[3], min_1s[3], max_5s[3], min_5s[3], max_30s[3], min_30s[3], ave_3s[3], ave_60s[3], ave_ratio[3], sensor_status, \
    max_1s[4], min_1s[4], max_5s[4], min_5s[4], max_30s[4], min_30s[4], ave_3s[4], ave_60s[4], ave_ratio[4], sensor_status, \
    max_1s[5], min_1s[5], max_5s[5], min_5s[5], max_30s[5], min_30s[5], ave_3s[5], ave_60s[5], ave_ratio[5], sensor_status);
    printf("\n%s\n%s\n", field_message, value_message);
    mysqldb_insert(mysql, TABLE_NAME6, field_message, value_message);
    close_connection(mysql);
}

void * common_feature()
{
    MYSQL *mysql;
    double e[6][200], max[6], min[6],  ave[6], time_temp4, t;
    int row = 0, i = 0, j = 0, k = 0, l = 0;
    char message1[60], message2[60], message3[60];

    t = get_system_time();

    time_temp4 = get_system_time3f();
    printf("\ndata cal start time: %f\n", time_temp4);

    //pthread_mutex_lock(&mutex_cal);
    mysql = mysql_init(NULL);
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }
    mysqldb_connect(mysql);

    mysqldb_query(mysql, "value1, value2, value3, value4, value5, value6", TABLE_NAME1, "1", "1 order by timestrap desc limit 200");

    for(row=0; row<6; row++)
        for (i=0; i<200; i++)
        {
            e[row][i] = data_check_array[row][i];
            //printf("%f\n", e[i]);
        }

    for(row=0; row<6; row++)
    {
        max[row] = search_max(e[row], 200);
        min[row] = search_min(e[row], 200);
        ave[row] = search_average(e[row], 200);
    }

    sprintf(message1, "%f, %f, %f, %f, %f, %f", min[0], min[1], min[2], min[3], min[4], min[5]);
    sprintf(message2, "%f, %f, %f, %f, %f, %f", max[0], max[1], max[2], max[3], max[4], max[5]);
    sprintf(message3, "%f, %f, %f, %f, %f, %f", ave[0], ave[1], ave[2], ave[3], ave[4], ave[5]);

    pthread_mutex_lock(&mutex_cal);
    i =  mysqldb_query_row(mysql, "count(*)", TABLE_NAME3, "1", "1");

    if(i >= 30){
        mysqldb_delete(mysql, TABLE_NAME3, "id asc", i-29);
        i--;
    }
    mysqldb_insert(mysql, TABLE_NAME3, "min_data_value1, min_data_value2, min_data_value3, min_data_value4, min_data_value5, min_data_value6", message1);
    mysqldb_alter(mysql, TABLE_NAME3, "id");
    //pthread_mutex_unlock(&mutex_min);

    //pthread_mutex_lock(&mutex_max);
    j = mysqldb_query_row(mysql, "count(*)", TABLE_NAME4, "1", "1");

    if(j >= 30){
        mysqldb_delete(mysql, TABLE_NAME4, "id asc", j-29);
        j--;
    }
    mysqldb_insert(mysql, TABLE_NAME4, "max_data_value1, max_data_value2, max_data_value3, max_data_value4, max_data_value5, max_data_value6", message2);
    mysqldb_alter(mysql, TABLE_NAME4, "id");
    //pthread_mutex_unlock(&mutex_max);

    //pthread_mutex_lock(&mutex_ave);
    k = mysqldb_query_row(mysql, "count(*)", TABLE_NAME5, "1", "1");

    if(k >= 60){
        mysqldb_delete(mysql, TABLE_NAME5, "id asc", k-59);
        k--;
    }
    mysqldb_insert(mysql, TABLE_NAME5, "ave_data_value1, ave_data_value2, ave_data_value3, ave_data_value4, ave_data_value5, ave_data_value6", message3);
    mysqldb_alter(mysql, TABLE_NAME5, "id");
    //pthread_mutex_unlock(&mutex_ave);

    l = mysqldb_query_row(mysql, "count(*)", TABLE_NAME6, "1", "1");

    if(l >= 300)
        mysqldb_delete(mysql, TABLE_NAME6, "timestrap asc", l-299);

    printf("\nok!\n");

    data_cal_change(i+1, j+1, k+1, t);
    pthread_mutex_unlock(&mutex_cal);

    time_temp4 = get_system_time3f();
    printf("\ndata cal finish time: %f\n", time_temp4);

    close_connection(mysql);
}
