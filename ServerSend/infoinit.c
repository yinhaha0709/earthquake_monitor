#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "../include/config.h"
#include "../include/infoinit.h"

char station_id[8], mode, version;
float longitude, latitude, strain, acceleration;
char topic_regpub[30], topic_regsub[33], topic_feature[29], topic_ontimepub[28], topic_ontimesub[31], topic_event[27];

void information_init()
{
    char str[30], temp[8], ch;

    FILE *fp;
    int i = 0, j = 0;
    int copy_status = 0;
    char topic_head_temp[16];

    memset(str, 0, 30);
    memset(temp, 0, 8);
    memset(&version, 0, 1);
    memset(&mode, 0, 1);

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

            //printf("%d\n", j);

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
                strncpy(&mode, str, j);
                mode = mode -'0';
                memset(str, 0, 30);
                break;
            case 6:
                strncpy(&version, str, j);
                version = version - '0';
                memset(&str, 0, 30);
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

    strcpy(topic_head_temp, MQTT_HEAD);
    strncat(topic_head_temp, station_id, 8);

    strcpy(topic_regpub, topic_head_temp);
    strcat(topic_regpub, MQTT_REGPUB);

    strcpy(topic_regsub, topic_head_temp);
    strcat(topic_regsub, MQTT_REGSUB);

    strcpy(topic_feature, topic_head_temp);
    strcat(topic_feature, MQTT_FEATURE);

    strcpy(topic_ontimepub, topic_head_temp);
    strcat(topic_ontimepub, MQTT_ONTIMEPUB);

    strcpy(topic_ontimesub, topic_head_temp);
    strcat(topic_ontimesub, MQTT_ONTIMESUB);

    strcpy(topic_event, topic_head_temp);
    strcat(topic_event, MQTT_EVENT);
/*
    sprintf(topic_head_temp, "%s%s", MQTT_HEAD, station_id);
    sprintf(topic_regpub, "%s%s", topic_head_temp, MQTT_REGPUB);
    sprintf(topic_regsub, "%s%s", topic_head_temp, MQTT_REGSUB);
    sprintf(topic_feature, "%s%s", topic_head_temp, MQTT_FEATURE);
    sprintf(topic_ontimepub, "%s%s", topic_head_temp, MQTT_ONTIMEPUB);
    sprintf(topic_ontimesub, "%s%s", topic_head_temp, MQTT_ONTIMESUB);
    sprintf(topic_event, "%s%s", topic_head_temp, MQTT_EVENT);
*/
    printf("%s\n%s\n%s\n%s\n%s\n%s\n", topic_regpub, topic_regsub, topic_feature, topic_ontimepub, topic_ontimesub, topic_event);
}
/*
int main(void)
{
    information_init();
}
*/