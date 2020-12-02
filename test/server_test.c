#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "../include/config.h"
#include "../include/mqtt.h"
#include "../include/infoinit.h"
//#include "../include/infoinit.h"

pthread_mutex_t mutex, mutex_row_check, mutex_cal, mutex_min, mutex_max, mutex_ave;
double sig_g[6];
double sys_time;
char station_id[8], mode, version;
float longitude, latitude, strain, acceleration;
short int simple_rate, simple_num;
char position_num[2], station_num[2];
char topic_regpub[30], topic_regsub[33], topic_feature[29], topic_ontimepub[28], topic_ontimesub[31], topic_event[27];
char threshold_status[6];

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
        int int_strain;
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


int main(void)
{
    char str[30], temp[8], ch;

    FILE *fp;
    int i = 0, j = 0;
    int copy_status = 0;

    uint8_t payload[32];
    memset(payload, 0, 32);
    VibtationReg_t Reg_temp;
    //union union_change U1;



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

   memcpy(&payload[0], Reg_temp.type_temp, 2);
    memcpy(&payload[2], &Reg_temp.long_temp, 4);
    memcpy(&payload[6], Reg_temp.id_temp, 8);
    memcpy(&payload[14], &Reg_temp.longitude_temp, 4);
    memcpy(&payload[18], &Reg_temp.latitude_temp, 4);
    memcpy(&payload[22], &Reg_temp.strain_temp, 4);
    memcpy(&payload[26], &Reg_temp.acceleration_temp, 4);
    memcpy(&payload[30], &Reg_temp.byte_mode, 1);
    memcpy(&payload[31], &Reg_temp.byte_version, 1);

    for(i=0; i<32; i++)
    {
        printf("%x ", payload[i]);
    } 

    printf("\n");

    vibration_mqtt_connect();
    vibration_subcribe(SERVER_REGSUB, 1);
    vibration_subcribe(SERVER_ONTIMESUB, 0);
    while(running)
    {
        vibration_publish(SERVER_REGPUB, payload, 32);
        sleep(1);
    }

    while(1)
    {
        sleep(1);
    }

    vibration_closeconn();
    return 0;
}