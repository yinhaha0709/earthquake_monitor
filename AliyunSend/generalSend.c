#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <mosquitto.h>
#include <string.h>
#include "../include/config.h"
#include "../include/mqtt.h"
#include "../include/cJSON.h"
#include "../include/generalSend.h"

void * generalFeature_Send()
{
    char *payload;
    cJSON *head = cJSON_CreateObject();
    cJSON *load = cJSON_CreateObject();

    cJSON_AddItemToObject(head, "method", cJSON_CreateString("thing.service.property.set"));
    cJSON_AddItemToObject(head, "id", cJSON_CreateString("10000"));
    cJSON_AddItemToObject(head, "params", load);
    
    cJSON_AddNumberToObject(load, "timestrap", timestrap);

    cJSON_AddNumberToObject(load, "min1_1s", min_1s[0]);
    cJSON_AddNumberToObject(load, "min2_1s", min_1s[1]);
    cJSON_AddNumberToObject(load, "min3_1s", min_1s[2]);
    cJSON_AddNumberToObject(load, "min4_1s", min_1s[3]);
    cJSON_AddNumberToObject(load, "min5_1s", min_1s[4]);
    cJSON_AddNumberToObject(load, "min6_1s", min_1s[5]);

    cJSON_AddNumberToObject(load, "max1_1s", max_1s[0]);
    cJSON_AddNumberToObject(load, "max2_1s", max_1s[1]);
    cJSON_AddNumberToObject(load, "max3_1s", max_1s[2]);
    cJSON_AddNumberToObject(load, "max4_1s", max_1s[3]);
    cJSON_AddNumberToObject(load, "max5_1s", max_1s[4]);
    cJSON_AddNumberToObject(load, "max6_1s", max_1s[5]);

    cJSON_AddNumberToObject(load, "min1_5s", min_5s[0]);
    cJSON_AddNumberToObject(load, "min2_5s", min_5s[1]);
    cJSON_AddNumberToObject(load, "min3_5s", min_5s[2]);
    cJSON_AddNumberToObject(load, "min4_5s", min_5s[3]);
    cJSON_AddNumberToObject(load, "min5_5s", min_5s[4]);
    cJSON_AddNumberToObject(load, "min6_5s", min_5s[5]);

    cJSON_AddNumberToObject(load, "max1_5s", max_5s[0]);
    cJSON_AddNumberToObject(load, "max2_5s", max_5s[1]);
    cJSON_AddNumberToObject(load, "max3_5s", max_5s[2]);
    cJSON_AddNumberToObject(load, "max4_5s", max_5s[3]);
    cJSON_AddNumberToObject(load, "max5_5s", max_5s[4]);
    cJSON_AddNumberToObject(load, "max6_5s", max_5s[5]);

    cJSON_AddNumberToObject(load, "min1_30s", min_30s[0]);
    cJSON_AddNumberToObject(load, "min2_30s", min_30s[1]);
    cJSON_AddNumberToObject(load, "min3_30s", min_30s[2]);
    cJSON_AddNumberToObject(load, "min4_30s", min_30s[3]);
    cJSON_AddNumberToObject(load, "min5_30s", min_30s[4]);
    cJSON_AddNumberToObject(load, "min6_30s", min_30s[5]);

    cJSON_AddNumberToObject(load, "max1_30s", max_30s[0]);
    cJSON_AddNumberToObject(load, "max2_30s", max_30s[1]);
    cJSON_AddNumberToObject(load, "max3_30s", max_30s[2]);
    cJSON_AddNumberToObject(load, "max4_30s", max_30s[3]);
    cJSON_AddNumberToObject(load, "max5_30s", max_30s[4]);
    cJSON_AddNumberToObject(load, "max6_30s", max_30s[5]);

    cJSON_AddNumberToObject(load, "ave1_3s", ave_3s[0]);
    cJSON_AddNumberToObject(load, "ave2_3s", ave_3s[1]);
    cJSON_AddNumberToObject(load, "ave3_3s", ave_3s[2]);
    cJSON_AddNumberToObject(load, "ave4_3s", ave_3s[3]);
    cJSON_AddNumberToObject(load, "ave5_3s", ave_3s[4]);
    cJSON_AddNumberToObject(load, "ave6_3s", ave_3s[5]);

    cJSON_AddNumberToObject(load, "ave1_60s", ave_60s[0]);
    cJSON_AddNumberToObject(load, "ave2_60s", ave_60s[1]);
    cJSON_AddNumberToObject(load, "ave3_60s", ave_60s[2]);
    cJSON_AddNumberToObject(load, "ave4_60s", ave_60s[3]);
    cJSON_AddNumberToObject(load, "ave5_60s", ave_60s[4]);
    cJSON_AddNumberToObject(load, "ave6_60s", ave_60s[5]);

    cJSON_AddNumberToObject(load, "ave_ratio1", ave_ratio[0]);
    cJSON_AddNumberToObject(load, "ave_ratio2", ave_ratio[1]);
    cJSON_AddNumberToObject(load, "ave_ratio3", ave_ratio[2]);
    cJSON_AddNumberToObject(load, "ave_ratio4", ave_ratio[3]);
    cJSON_AddNumberToObject(load, "ave_ratio5", ave_ratio[4]);
    cJSON_AddNumberToObject(load, "ave_ratio6", ave_ratio[5]);

    cJSON_AddNumberToObject(load, "sensor_status1", sensor_status[0]);
    cJSON_AddNumberToObject(load, "sensor_status2", sensor_status[1]);
    cJSON_AddNumberToObject(load, "sensor_status3", sensor_status[2]);
    cJSON_AddNumberToObject(load, "sensor_status4", sensor_status[3]);
    cJSON_AddNumberToObject(load, "sensor_status5", sensor_status[4]);
    cJSON_AddNumberToObject(load, "sensor_status6", sensor_status[5]);

    cJSON_AddItemToObject(head, "version", cJSON_CreateString("1.0.0"));

    payload = cJSON_Print(head);
    printf("%s\n", payload);

    my_mqtt_publish(MQTT_TOPIC_PUB, payload);
}
