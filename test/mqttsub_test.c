#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mosquitto.h>
#include <string.h>
#include "../include/config.h"

int running = 1;


void my_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
    printf("receive a message of %s: %s\n", (char *)msg->topic, (char *)msg->payload);
    running = 0;
    mosquitto_disconnect(mosq);
}

int main(int argc, char*argv[])
{
    bool session = MQTT_SESSION;
    struct mosquitto *mosq = NULL;
    char *clientid = MQTT_CLIENTID;
    char *ip = MQTT_HOST;
    int port = MQTT_PORT;
    int keep_alive = KEEP_ALIVE;
    char *topic = MQTT_TOPIC_SUB;


    mosquitto_lib_init();
    mosq = mosquitto_new(clientid, session, NULL);

    if(!mosq){
        printf("mqttsub_connect create() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }
    printf("create mosquitto successfully!\n");

    mosquitto_message_callback_set(mosq, my_message_callback);

    if(mosquitto_username_pw_set(mosq, MQTT_USER, MQTT_PASSWORD) != MOSQ_ERR_SUCCESS){
        printf("user and passwd fail!\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }
    
    if(mosquitto_connect(mosq, ip, port, keep_alive) != MOSQ_ERR_SUCCESS){
        printf("mosqsub_connect() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }
    printf("connect %s:%d successfully!\n", ip, port);

    if(mosquitto_subscribe(mosq, NULL, topic, 0) != MOSQ_ERR_SUCCESS){
        printf("mqttsub_test() error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }
    else
    {
        printf("subcribe qos0 success!\n");
    }

    int loop = mosquitto_loop_start(mosq);
    if(loop != MOSQ_ERR_SUCCESS){
        printf("mosquitto loop error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }

    while(running){
        sleep(1);
    }

    mosquitto_loop_stop(mosq, false);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}