#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "../include/config.h"
#include "../include/database.h"
#include "../include/searchaverage.h"
#include "../include/searchmax.h"
#include "../include/searchmin.h"
#include "../include/datacharacteric.h"
#include "../include/systime.h"

void data_cal_change(int i, int j, int k)
{
    MYSQL *mysql;
    double t, min_array[30], max_array[30], ave_array[60];
    float min_1s, max_1s, min_5s, max_5s, min_30s, max_30s, ave_3s, ave_60s, ave_ratio, sensor_status = 3;
    int x = 0;
    char field_message[200], value_message[120];

    char tunnel = "1";

    mysql = mysql_init(NULL);
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }
    mysqldb_connect(mysql);

    mysqldb_query(mysql, "min_data_value", TABLE_NAME3, "1", "1 order by id desc limit 30");
    for(x=0; x<i; x++)
        min_array[x] = atof(row[x]);

    mysqldb_query(mysql, "max_data_value", TABLE_NAME4, "1", "1 order by id desc limit 30");
    for(x=0; x<j;x++)
        max_array[x] = atof(row[x]);

    mysqldb_query(mysql, "ave_data_value", TABLE_NAME5, "1", "1 order by id desc limit 60");
    for(x=0; x<k; x++)
        ave_array[x] = atof(row[x]);

    min_1s = min_array[0];
    max_1s = max_array[0];

    if(i < 5){
        min_5s = search_min(min_array, i);
        min_30s = min_5s;
    }
    else if(i < 30){
        min_5s = search_min(min_array, 5);
        min_30s = search_min(min_array, i);
    }
    else if(i >= 30){
        min_5s = search_min(min_array, 5);
        min_30s = search_min(min_array, 30);
    }

    if(j < 5){
        max_5s = search_max(max_array, i);
        max_30s = max_5s;
    }
    else if(j < 30){
        max_5s = search_max(max_array, 5);
        max_30s = search_max(max_array, i);
    }
    else if(j >= 30){
        max_5s = search_max(max_array, 5);
        max_30s = search_max(max_array, 30);
    }

    if(k < 3){
        ave_3s = search_average(ave_array, k);
        ave_60s = ave_3s;
    }
    else if(k < 60){
        ave_3s = search_average(ave_array, 3);
        ave_60s = search_average(ave_array, k);
    }
    else if(k >= 60){
        ave_3s = search_average(ave_array, 3);
        ave_60s = search_average(ave_array, 60);
    }

    if(ave_3s == 0.0)
        ave_ratio = -1;
    else
        ave_ratio = ave_60s / ave_3s;

    t = get_system_time();

    strcpy(field_message, "timestrap, tunnel_ID, max_value_1s, min_value_1s, max_value_5s, min_value_5s, max_value_30s, min_value_30s, ave_value_3s, ave_value_60s, ave_ratio, sensor_status");
    sprintf(value_message, "%f, %s, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f", t, tunnel, max_1s, min_1s, max_5s, min_5s, max_30s, min_30s, ave_3s, ave_60s, ave_ratio, sensor_status);
    mysqldb_insert_cal(mysql, TABLE_NAME6, field_message, value_message);
}

void data_calculation_operation()
{
    MYSQL *mysql;
    double e[200], f[1000], g[6000], max, min,  ave;
    int i = 0, j = 0, k = 0;
    char message1[20], message2[20], message3[20];

    mysql = mysql_init(NULL);
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }
    mysqldb_connect(mysql);

    mysqldb_query(mysql, "value", TABLE_NAME1, "1", "1 order by timestrap desc limit 200");
    for (i=0; i<200; i++)
        e[i] = atof(row[i]);
    
    max = search_max(e, 200);
    min = search_min(e, 200);
    ave = search_average(e, 200);
    sprintf(message1, "%f", min);
    sprintf(message2, "%f", max);
    sprintf(message3, "%f", ave);

    mysqldb_query(mysql, "count(*)", TABLE_NAME3, "1", "1");
    i = atoi(row[0]);
    if(i >= 30){
        mysqldb_delete(mysql, TABLE_NAME3, "min_data_value asc", "1");
    }
    mysqldb_insert_cal(mysql, TABLE_NAME3, "min_data_value", message1);
    mysqldb_alter(mysql, TABLE_NAME3, "id");

    mysqldb_query(mysql, "count(*)", TABLE_NAME4, "1", "1");
    j = atoi(row[0]);
    if(j >= 30){
        mysqldb_delete(mysql, TABLE_NAME4, "max_data_value asc", "1");
    }
    mysqldb_insert_cal(mysql, TABLE_NAME4, "max_data_value", message2);
    mysqldb_alter(mysql, TABLE_NAME4, "id");

    mysqldb_query(mysql, "count(*)", TABLE_NAME5, "1", "1");
    k = atoi(row[0]);
    if(k >= 60){
        mysqldb_delete(mysql, TABLE_NAME5, "ave_data_value asc", "1");
    }
    mysqldb_insert_cal(mysql, TABLE_NAME5, "ave_data_value", message3);
    mysqldb_alter(mysql, TABLE_NAME5, "id");

    data_cal_change(i, j, k);
}