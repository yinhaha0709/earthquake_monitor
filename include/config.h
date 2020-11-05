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

#define MQTT_HOST "iot-cn-m7r1w4jj81b.mqtt.iothub.aliyuncs.com"
//#define MQTT_HOST "localhost"
#define MQTT_PORT 1883
#define MQTT_TOPIC_SUB "/g1q4Ckn02eI/D001_test/user/get"
#define MQTT_TOPIC_PUB "/sys/g1q4Ckn02eI/D001_test/thing/event/property/post"
//#define MQTT_TOPIC_REG "/g1q4Ckn02eI/D001_test/user/update"
#define MQTT_USER "D001_test&g1q4Ckn02eI"
#define MQTT_PASSWORD "56617D05855C0B2293BBF27414F4CB96327C9900"
#define MQTT_CLIENTID "12345|securemode=3,signmethod=hmacsha1|"
#define MQTT_SESSION true;

#define MESSAGE_INT "message_int_content"
#define SIMPLE_RATE 200
#define TUNNEL '1'
#define SENSOR_STATUS 3
#define KEEP_ALIVE 60

#define DATA_PORT "/dev/ttyUSB0"
#define NET_PORT "/dev/ttyUSB3"

extern double min_check_array[30];
extern double max_check_array[30];
extern double ave_check_array[60];
extern double data_check_array[200];

extern int running;

extern pthread_mutex_t mutex, mutex_row_check, mutex_cal;

#endif