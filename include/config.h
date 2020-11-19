#ifndef __CONFIG_H__
#define __CONFIG_H__

//#include <mosquitto.h>
//#include <mysql/mysql.h>
//#include <pthread.h>

#define SHORT_BUF_SIZE 1024
#define LONG_BUF_SIZE 2048

#define MYSQL_HOST    "localhost"
#define MYSQL_USER    "root"
#define MYSQL_PASSWD  "zncg123456"
#define DB_NAME "vibration"
#define TABLE_NAME1 "ontime_data"
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

#define SERVER_HOST "120.55.56.36"
#define SERVER_PORT 1883
#define SERVER_USER "USER"
#define SERVER_PASSWORD "password"
#define SERVER_QOS 1
#define MQTT_HEAD "vibrate/"
#define MQTT_REGPUB "/register/data"
#define MQTT_REGSUB "/register/control"
#define MQTT_FEATURE "/feature/data"
#define MQTT_ONTIMEPUB "/ontime/data"
#define MQTT_ONTIMESUB "/ontime/control"
#define MQTT_EVENT "/event/data"


#define SERVER_REGPUB "vibrate/GZ.23212/register/data"
#define SERVER_REGSUB "vibrate/GZ.23212/register/control"
#define SERVER_FEATURE "vibrate/GZ.23212/feature/data"
#define SERVER_ONTIMESUB "vibrate/GZ.23212/ontime/control"
#define SERVER_ONTIMEPUB "vibrate/GZ.23212/ontime/data"
#define SERVER_EVENT "vibrate/GZ.23212/event/data"

#define MESSAGE_INT "message_int_content"
#define SIMPLE_RATE 200
#define TUNNEL '1'
#define SENSOR_STATUS 3
#define KEEP_ALIVE 60

#define ENDIAN 1

#define DATA_PORT "/dev/signal_port"
#define NET_PORT "/dev/net_port"

extern double min_check_array[6][30];
extern double max_check_array[6][30];
extern double ave_check_array[6][60];
extern double data_check_array[6][200];

extern float sig_g[6];

extern float min_1s[6], max_1s[6], min_5s[6], max_5s[6], min_30s[6], max_30s[6], ave_3s[6], ave_60s[6], ave_ratio[6];
extern float sensor_status[6];
extern double timestrap;

extern int running;
extern int ontime;

extern pthread_mutex_t mutex, mutex_row_check, mutex_cal, mutex_min, mutex_max, mutex_ave;

extern struct mosquitto *mosq;
extern struct mosquitto *mosq1;

extern char station_id[8], mode, version;
extern float longitude, latitude, strain, acceleration;

extern char *topic_regpub, *topic_regsub, *topic_feature, *topic_ontimepub, *topic_ontimesub, *topic_event;

#endif