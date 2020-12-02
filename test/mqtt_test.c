#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "../include/config.h"
#include "../include/registerSend.h"
#include "../include/mqtt.h"
#include "../include/cJSON.h"

pthread_mutex_t mutex, mutex_row_check, mutex_cal, mutex_min, mutex_max, mutex_ave;
double sig_g[6];
double sys_time;
char station_id[8], mode, version;
float longitude, latitude, strain, acceleration;
short int simple_rate, simple_num;
char position_num[2], station_num[2];
char topic_regpub[30], topic_regsub[33], topic_feature[29], topic_ontimepub[28], topic_ontimesub[31], topic_event[27];
char threshold_status[6];


int main(void)
{
    my_mqtt_connect();
    sleep(1);
    station_reg();
    //my_mqtt_closeconn();
}