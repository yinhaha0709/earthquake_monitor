#include <stdio.h>
#include <string.h>
#include "../include/config.h"
#include "../include/mqtt.h"
#include "../include/systime.h"
#include "../include/ontime.h"

void * ontime_send(void * arg)
{
    float ontime_data_send[50][6];
    int i, j, k;
    double ontime_time;

    pthread_mutex_lock(&mutex);
    ontime_time = ((double*)arg)[0];

    for(i=0; i<50; i++)
    {
        ontime_data_send[i][0] = ((double*)arg)[i * 7 + 1] * 1000;
        ontime_data_send[i][1] = ((double*)arg)[i * 7 + 2] * 1000;
        ontime_data_send[i][2] = ((double*)arg)[i * 7 + 3] * 1000;
        ontime_data_send[i][3] = ((double*)arg)[i * 7 + 4] * 1000;
        ontime_data_send[i][4] = ((double*)arg)[i * 7 + 5] * 1000;
        ontime_data_send[i][5] = ((double*)arg)[i * 7 + 6] * 1000;
    }
    pthread_mutex_unlock(&mutex);

    char type[2] = "wc";
    int ontime_long = 1289;
    int block_long = 209;
    //int block_num = 0;
    char num, num_next, tunnel;
    char endian = ENDIAN;

    uint8_t payload[ontime_long];

    memcpy(&payload[0], type, 2);
    memcpy(&payload[2], &ontime_long, 4);
    memcpy(&payload[6], &ontime_block_num, 4);
    memcpy(&payload[10], station_id, 8);
    memcpy(&payload[18], position_num, 2);
    memcpy(&payload[20], &mode, 1);
    memcpy(&payload[21], station_num, 2);
    memcpy(&payload[23], &ontime_time, 8);
    memcpy(&payload[31], &simple_num, 2);
    memcpy(&payload[33], &simple_rate, 2);

    j = 35;

    for(i=0; i<6; i++)
    {
        num = i + 1;

        num_next = i + 2;
        if(i >=5)
            num_next = 0;
        
        tunnel = i;

        memcpy(&payload[j], &num, 1);
        memcpy(&payload[j + 1], &num_next, 1);
        memcpy(&payload[j + 2], &endian, 1);
        memcpy(&payload[j + 3], &block_long, 4);
        memcpy(&payload[j + 7], &tunnel, 1);
        memcpy(&payload[j + 8], threshold_status + i, 1);

        for(k=0; k<50; k++)
        {
            memcpy(&payload[j + 9 + (4 * k)], &ontime_data_send[k][i], 4);
        }

        j = j + 209;
    }

    for(i=0; i<ontime_long; i++)
    {
        printf("%x", payload[i]);
    }

    printf("\n");

    vibration_publish(topic_ontimepub, payload, ontime_long);
}