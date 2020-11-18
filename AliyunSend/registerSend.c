#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <mosquitto.h>
#include <string.h>
#include "../include/config.h"
#include "../include/mqtt.h"
#include "../include/cJSON.h"
#include "../include/registerSend.h"
/*
union union_change
{
    
    uint8_t i_char_bit;
    char    i_char_char;
    int i_char_int;
};
*/
void station_reg()
{
    char str[30], station_id[8], temp[8], mode[1], version[1], ch;
    

    FILE *fp;
    int i = 0;
    int j = 0;
    int copy_status = 0;
    float longitude, latitude, strain, acceleration;
    int version_int , mode_int;
    char *payload;
    //union union_change U1;
    cJSON *head = cJSON_CreateObject();
    cJSON *load = cJSON_CreateObject();

    memset(str, 0, 30);
    memset(temp, 0, 8);
    memset(version, 0, 1);
    memset(mode, 0, 1);

    fp = fopen("../data/station_message.txt", "r");
    if (fp == NULL)
    {
        printf("fail to open reg file!\n");
        return;
    }

    while ((ch = fgetc(fp)) != EOF && ch != '\377')
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
                strncpy(mode, str, j);
                memset(str, 0, 30);
                //mode[0] = temp[0];
                //memset(temp, 0, 8);
                //printf("%s %c\n", mode, mode[0]);
                break;
            case 6:
                strncpy(version, str, j);
                //version[0] = temp[0];
                memset(str, 0, 30);
                //printf("%s %c\n", version, version[0]);
                //memset(temp, 0, 8);
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
    //printf("ok\n");
    /*
    U1.i_char_char = version[0];
    printf("%x\n%c\n%d\n", U1.i_char_bit, U1.i_char_char, U1.i_char_int);
    version_int = U1.i_char_int;

    U1.i_char_char = mode[0];
    printf("%x\n%c\n%d\n", U1.i_char_bit, U1.i_char_char, U1.i_char_int);
    mode_int = U1.i_char_int;
    */

    cJSON_AddItemToObject(head, "method", cJSON_CreateString("thing.service.property.set"));
    cJSON_AddItemToObject(head, "id", cJSON_CreateString("10000"));
    cJSON_AddItemToObject(head, "params", load);
    cJSON_AddItemToObject(load, "ID", cJSON_CreateString(station_id));
    cJSON_AddNumberToObject(load, "longitude", longitude);
    cJSON_AddNumberToObject(load, "latitude", latitude);
    cJSON_AddNumberToObject(load, "strain", strain);
    cJSON_AddNumberToObject(load, "acceleration", acceleration);
    cJSON_AddItemToObject(load, "mode", cJSON_CreateString("1"));
    //memset(cJSON->valuestring, 0, 8);
    cJSON_AddItemToObject(load, "version", cJSON_CreateString("1"));
    cJSON_AddItemToObject(head, "version", cJSON_CreateString("1.0.0"));   

    payload = cJSON_Print(head);
    printf("%s\n", payload);
    //printf("ok\n");


    my_mqtt_publish(MQTT_TOPIC_PUB, payload);
    my_mqtt_closeconn();
    my_mqtt_subcribe(MQTT_TOPIC_SUB);
}
