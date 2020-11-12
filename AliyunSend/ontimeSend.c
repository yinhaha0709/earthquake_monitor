#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <mosquitto.h>
#include <string.h>
#include "../include/config.h"
#include "../include/mqtt.h"
#include "../include/cJSON.h"
#include "../include/ontimeSend.h"

void * ontimeSend_Aliyun()
{
    int i = 0;
    float data[6];
    cJSON *head = cJSON_CreateObject();
    cJSON *load = cJSON_CreateObject();
    char *payload;

    for(i=0; i<6; i++)
    {
        data[i] = sig_g[i];
    }

    cJSON_AddItemToObject(head, "method", cJSON_CreateString("thing.service.property.set"));
    cJSON_AddItemToObject(head, "id", cJSON_CreateString("10000"));
    cJSON_AddItemToObject(head, "params", load);
    cJSON_AddNumberToObject(load, "ontime1", data[0]);
    cJSON_AddNumberToObject(load, "ontime2", data[1]);
    cJSON_AddNumberToObject(load, "ontime3", data[2]);
    cJSON_AddNumberToObject(load, "ontime4", data[3]);
    cJSON_AddNumberToObject(load, "ontime5", data[4]);
    cJSON_AddNumberToObject(load, "ontime6", data[5]);
    cJSON_AddItemToObject(head, "version", cJSON_CreateString("1.0.0"));

    payload = cJSON_Print(head);
    printf("%s\n", payload);

    my_mqtt_publish(MQTT_TOPIC_PUB, payload);
}
