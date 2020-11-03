#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mosquitto.h>
#include <string.h>
#include "../include/config.h"

void my_connect_callback(struct mosquitto *mosq, void *obj, int rc)
{
    printf("connect callback\n");
}

int main(int argc, char*argv[])
{
    bool session = MQTT_SESSION;
    struct mosquitto *mosq = NULL;
    char *clientid = MQTT_CLIENTID;
    char *ip = MQTT_HOST;
    int port = MQTT_PORT;
    int keep_alive = KEEP_ALIVE;
    char message_temp[BUF_SIZE] = "hello test!";
    char *topic = MQTT_TOPIC;

    mosquitto_lib_init();
    mosq = mosquitto_new(clientid, session, NULL);

    if(!mosq){
        printf("mqttpub_connect create() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }
    printf("create mosquitto successfully!\n");

    mosquitto_connect_callback_set(mosq, my_connect_callback);

        if(mosquitto_username_pw_set(mosq, MQTT_USER, MQTT_PASSWORD) != MOSQ_ERR_SUCCESS){
        printf("user and passwd fail!\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }
    
    if(mosquitto_connect(mosq, ip, port, keep_alive) != MOSQ_ERR_SUCCESS){
        printf("mosqpub_connect() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }
    printf("connect %s:%d successfully!\n", ip, port);

    int loop = mosquitto_loop_start(mosq);
    if(loop != MOSQ_ERR_SUCCESS){
        printf("mosquitto loop error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }

    if(mosquitto_publish(mosq, NULL, topic, strlen(message_temp)+1, message_temp, 0, 0) != MOSQ_ERR_SUCCESS){
        printf("mqttpub_publish() error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }
    else
    {
        printf("publish qos0 success!\n\n");
    }

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    
    sleep(5);
    return 0;
}