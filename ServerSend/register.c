#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "../include/config.h"
#include "../include/mqtt.h"
#include "../include/register.h"
/*
char station_id[8], mode, version;
float longitude, latitude, strain, acceleration;
*/
typedef struct VibtationReg_T
{
    union
    {
        char type_temp[2];
        uint8_t byte_type[2];
    };

    union
    {
        int long_temp;
        uint8_t byte_long[4];
    };

    union
    {
        char id_temp[8];
        uint8_t byte_id[8];
    };

    union
    {
        float longitude_temp;
        uint8_t byte_longitude[4];
    };

    union
    {
        float latitude_temp;
        uint8_t byte_latitude[4];
    };

    union
    {
        float strain_temp;
        uint8_t byte_strain[4];
    };

    union
    {
        float acceleration_temp;
        uint8_t byte_acceleration[4];
    };

    union
    {
        char mode_temp;
        uint8_t byte_mode;
    };

    union
    {
        char version_temp;
        uint8_t byte_version;
    };
}VibtationReg_t;


void register_send()
{
/*
    char str[30], temp[8], ch;

    FILE *fp;
    int i = 0, j = 0;
    int copy_status = 0;
*/
    int i = 0;
    uint8_t payload[32];
    memset(payload, 0, 32);
    VibtationReg_t Reg_temp;
    //union union_change U1;
/*
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
                strncpy(version, str, j);
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
    */

    strcpy(Reg_temp.type_temp, "re");
    printf("%x %x\n", Reg_temp.type_temp[0], Reg_temp.type_temp[1]);

    Reg_temp.long_temp = 32;
    printf("%x %x %x %x\n", Reg_temp.byte_long[0], Reg_temp.byte_long[1], Reg_temp.byte_long[2], Reg_temp.byte_long[3]);

    strcpy(Reg_temp.id_temp, station_id);


    for(i=0; i<8; i++)
        printf("%x ", Reg_temp.byte_id[i]);

    printf("\n");

    Reg_temp.longitude_temp = longitude;
    printf("%x %x %x %x\n", Reg_temp.byte_longitude[0], Reg_temp.byte_longitude[1], Reg_temp.byte_longitude[2], Reg_temp.byte_longitude[3]);

    Reg_temp.latitude_temp = latitude;
    printf("%x %x %x %x\n", Reg_temp.byte_latitude[0], Reg_temp.byte_latitude[1], Reg_temp.byte_latitude[2], Reg_temp.byte_latitude[3]);

    Reg_temp.strain_temp = strain;
    printf("%x %x %x %x\n", Reg_temp.byte_strain[0], Reg_temp.byte_strain[1], Reg_temp.byte_strain[2], Reg_temp.byte_strain[3]);

    Reg_temp.acceleration_temp = acceleration;
    printf("%x %x %x %x\n", Reg_temp.byte_acceleration[0], Reg_temp.byte_acceleration[1], Reg_temp.byte_acceleration[2], Reg_temp.byte_acceleration[3]);

    Reg_temp.mode_temp = mode;
    printf("%x\n", Reg_temp.mode_temp);

    Reg_temp.version_temp = version;
    printf("%x\n", Reg_temp.version_temp);

    //char payload[SHORT_BUF_SIZE] = {0};
    //vibration_mqtt_connect();
    //sleep(1);

    //sprintf(payload, "re%04s11.23212%04s%04s%04s%04s11", (char)Reg_temp.long_temp, (char)Reg_temp.int_longtitude, (char)Reg_temp.int_latitude, (char)Reg_temp.int_strain, (char)Reg_temp.int_acceleration);
    //printf("%x\n", payload);

   memcpy(&payload[0], Reg_temp.byte_type, 2);
    memcpy(&payload[2], Reg_temp.byte_long, 4);
    memcpy(&payload[6], Reg_temp.byte_id, 8);
    memcpy(&payload[14], Reg_temp.byte_longitude, 4);
    memcpy(&payload[18], Reg_temp.byte_latitude, 4);
    memcpy(&payload[22], Reg_temp.byte_strain, 4);
    memcpy(&payload[26], Reg_temp.byte_acceleration, 4);
    memcpy(&payload[30], &Reg_temp.byte_mode, 1);
    memcpy(&payload[31], &Reg_temp.byte_version, 1);

    for(i=0; i<32; i++)
    {
        printf("%x ", payload[i]);
    } 

    printf("\n");

    vibration_mqtt_connect();
    vibration_subcribe(topic_regsub);
    vibration_subcribe(topic_ontimesub);
    while(running)
    {
        vibration_publish(topic_regpub, payload, 32);
        sleep(1);
    }

}