#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "../include/config.h"
#include "../include/mqtt.h"

int main(void)
{
    char *type = "re";
    int pay_long = 31;
    char *stationID = "11_23212";
    float longtitude = 100.0;
    float latitude = 35.0;
    float strain = 2.0;
    float acceleration = 5.0;
    char model = '1';
    char version = '1';

    char payload[SHORT_BUF_SIZE] = {0};
    vibration_mqtt_connect();
    sleep(1);

    sprintf(payload, "%s%d%s%f%f%f%f%c%c", type, pay_long, stationID, longtitude, latitude, strain, acceleration, model, version);

    printf("%s\n", payload);

    vibration_publish(SERVER_REGPUB, payload);
    vibration_subcribe(SERVER_REGSUB);
}