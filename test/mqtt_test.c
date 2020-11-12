#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "../include/config.h"
#include "../include/registerSend.h"
#include "../include/mqtt.h"
#include "../include/cJSON.h"

int main(void)
{
    my_mqtt_connect();
    sleep(1);
    station_reg();
    //my_mqtt_closeconn();
}