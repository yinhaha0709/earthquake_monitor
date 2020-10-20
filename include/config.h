#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <mysql/mysql.h>
#include <pthread.h>

#define BUF_SIZE 30
#define MYSQL_HOST    "localhost"
#define MYSQL_USER    "root"
#define MYSQL_PASSWD  "zncg123456"
#define DB_NAME "workbench_test"
#define TABLE_NAME1 "data_test"
#define TABLE_NAME2 "data_message"
#define TABLE_NAME3 "data_min"
#define TABLE_NAME4 "data_max"
#define TABLE_NAME5 "data_ave"
#define TABLE_NAME6 "data_send"
#define MESSAGE_INT "message_int_content"
#define SIMPLE_RATE 200
#define TUNNEL '1'
#define SENSOR_STATUS 3

#endif