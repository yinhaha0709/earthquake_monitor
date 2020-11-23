#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../include/config.h"
#include "../include/stationreg.h"
#include "../include/mqtt.h"
#include "../include/cJSON.h"

union union_change
{
    
    uint8_t i_char_bit;
    char    i_char_char;
};

void station_reg()
{
    char str[30], station_id[8], temp[8], mode, version, ch;
    

    FILE *fp;
    int i = 0;
    int j = 0;
    int copy_status = 0;
    int version_temp, str_long;
    float longitude, latitude, strain, acceleration;
    union union_change U1;

    memset(str, 0, 30);
    memset(temp, 0, 8);

    fp = fopen("../data/station_message.txt", "r");
    if (fp == NULL)
    {
        printf("fail to open reg file!\n");
        return;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            copy_status = 0;

            switch (i)
            {
            case 0:
                strncpy(station_id, str, j);
                printf("%s\n", station_id);
                memset(str, 0, 30);
                break;
            case 1:
                strncpy(temp, str, j);
                longitude = atof(temp);
                memset(str, 0, 30);
                printf("%s\n%f\n", temp, longitude);
                memset(temp, 0, 8);
                break;
            case 2:
                strncpy(temp, str, j);
                latitude = atof(temp);
                memset(str, 0, 30);
                printf("%s\n%f\n", temp, latitude);
                memset(temp, 0, 8);
                break;
            case 3:
                strncpy(temp, str, j);
                strain = atof(temp);
                memset(str, 0, 30);
                printf("%s\n%f\n", temp, strain);
                memset(temp, 0, 8);
                break;
            case 4:
                strncpy(temp, str, j);
                acceleration = atof(temp);
                memset(str, 0, 30);
                printf("%s\n%f\n", temp, acceleration);
                memset(temp, 0, 8);
                break;
            case 5:
                strncpy(temp, str, j);
                memset(str, 0, 30);
                mode = temp[0];
                memset(temp, 0, 8);
                printf("%c\n", mode);
                break;
            case 6:
                strncpy(temp, str, j);
                version = temp[0];
                memset(str, 0, 30);
                printf("%s\n%c\n", temp, version);
                memset(temp, 0, 8);
                break;
            default:
                break;
            }

            j = 0;
            i++;
        }

        if (copy_status == 1)
        {
            str[j] = ch;
            j++;
        }

        if (ch == ' ')
            copy_status = 1;
    }

    fclose(fp);
    U1.i_char_char = version;
    printf("%x\n%c\n", U1.i_char_bit, U1.i_char_char);
    str_long = sizeof("{\"method\":\"thing.service.property.post\",\"id\":\"1000000000\",\"params\":{\"ID\":\"\",\"longitude\":,\"latitude\":,\"strain\":,\"acceleration\":,\"mode\":\"\",\"version\":},\"version\":\"1.0.0\"}") + sizeof(station_id) + sizeof(longitude) + sizeof(latitude) + sizeof(strain) + sizeof(acceleration) + sizeof(mode) + sizeof(version);
    printf("%d\n", str_long);

    bool session = MQTT_SESSION;
    struct mosquitto *mosq = NULL;
    char *clientid = MQTT_CLIENTID;
    char *ip = MQTT_HOST;
    int port = MQTT_PORT;
    int keep_alive = KEEP_ALIVE;
    cJSON *head = cJSON_CreateObject();
    cJSON *load = cJSON_CreateObject();
    int mid = 123;

    char *buf;

    cJSON_AddItemToObject(head, "method", cJSON_CreateString("thing.service.property.set"));
    cJSON_AddItemToObject(head, "id", cJSON_CreateString("10000"));
    cJSON_AddItemToObject(head, "params", load);
    cJSON_AddItemToObject(load, "ID", cJSON_CreateString(station_id));
    cJSON_AddNumberToObject(load, "longitude", longitude);
    cJSON_AddNumberToObject(load, "latitude", latitude);
    cJSON_AddNumberToObject(load, "strain", strain);
    cJSON_AddNumberToObject(load, "acceleration", acceleration);
    cJSON_AddItemToObject(load, "mode", cJSON_CreateString(&mode));
    cJSON_AddItemToObject(load, "version", cJSON_CreateString(&version));
    cJSON_AddItemToObject(head, "version", cJSON_CreateString("1.0.0"));

    buf = cJSON_Print(head);
    printf("%s\n", buf);    

    my_mqtt_connect();
    my_mqtt_publish(MQTT_TOPIC_PUB, buf);
    my_mqtt_subcribe(MQTT_TOPIC_SUB);
}
/*
int main()
{
    station_reg();
}
*/