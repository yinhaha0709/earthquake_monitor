#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mosquitto.h>
#include <string.h>
#include "../include/config.h"
#include "../include/mqtt.h"
#include "../include/cJSON.h"

int running;

char station_id[8], mode, version;
float longitude, latitude, strain, acceleration;

struct mosquitto *mosq = NULL;
struct mosquitto *mosq1 = NULL;

typedef struct RegSub_T
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
        short auth_temp;
        uint8_t byte_auth[2];
    };

}RegSub_t;

void my_mqtt_connect()
{
    //struct mosquitto *mosq = NULL;
    char *clientid = MQTT_CLIENTID;
    char *ip = MQTT_HOST;
    int port = MQTT_PORT;
    int keep_alive = KEEP_ALIVE;
    bool session = MQTT_SESSION;

    mosquitto_lib_init();
    mosq = mosquitto_new(clientid, session, NULL);

    if(!mosq){
        printf("mqttpub_connect create() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("create mosquitto successfully!\n");

    //mosquitto_message_callback_set(mosq, my_message_callback);

    if(mosquitto_username_pw_set(mosq, MQTT_USER, MQTT_PASSWORD) != MOSQ_ERR_SUCCESS){
        printf("user and passwd fail!\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    
    if(mosquitto_connect(mosq, ip, port, keep_alive) != MOSQ_ERR_SUCCESS){
        printf("mosqpub_connect() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("connect %s:%d successfully!\n", ip, port);

    int loop = mosquitto_loop_start(mosq);
    if(loop != MOSQ_ERR_SUCCESS){
        printf("mosquitto loop error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }

}

void my_mqtt_publish(char *topic, char *payload)
{
    int mid = 123;

    if(mosquitto_publish(mosq, &mid, topic, strlen(payload)+1, payload, 0, 0) != MOSQ_ERR_SUCCESS){
        printf("mqttpub_publish() error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    else
    {
        printf("publish qos0 success!\n\n");
    }
}

void my_mqtt_subcribe(char *topic)
{
    char *clientid = MQTT_CLIENTID;
    char *ip = MQTT_HOST;
    int port = MQTT_PORT;
    int keep_alive = KEEP_ALIVE;
    bool session = MQTT_SESSION;

    mosquitto_lib_init();
    mosq = mosquitto_new(clientid, session, NULL);

    if(!mosq){
        printf("mqttpub_connect create() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("create mosquitto successfully!\n");

    mosquitto_message_callback_set(mosq, my_message_callback);

    if(mosquitto_username_pw_set(mosq, MQTT_USER, MQTT_PASSWORD) != MOSQ_ERR_SUCCESS){
        printf("user and passwd fail!\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    
    if(mosquitto_connect(mosq, ip, port, keep_alive) != MOSQ_ERR_SUCCESS){
        printf("mosqpub_connect() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("connect %s:%d successfully!\n", ip, port);

    int loop = mosquitto_loop_start(mosq);
    if(loop != MOSQ_ERR_SUCCESS){
        printf("mosquitto loop error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    running = 1;

    if(mosquitto_subscribe(mosq, NULL, topic, 0) != MOSQ_ERR_SUCCESS){
        printf("mqttsub_test() error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    else
    {
        printf("subcribe qos0 success!\n");
    }

    while(running)
    {
        sleep(1);
    }

    mosquitto_loop_stop(mosq, false);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

void my_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
    printf("receive a message of %s: %s\n", (char *)msg->topic, (char *)msg->payload);
    running = 0;
    mosquitto_disconnect(mosq);
}


void my_mqtt_closeconn()
{
    mosquitto_disconnect(mosq);
    mosquitto_loop_stop(mosq, false);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    printf("mqtt close\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void vibration_mqtt_connect()
{
    //struct mosquitto *mosq = NULL;
    char *clientid = "12345";
    char *ip = SERVER_HOST;
    int port = SERVER_PORT;
    int keep_alive = KEEP_ALIVE;
    bool session = MQTT_SESSION;

    mosquitto_lib_init();
    mosq1 = mosquitto_new(clientid, session, NULL);

    if(!mosq1){
        printf("mqttpub_connect create() failed\n");
        mosquitto_destroy(mosq1);
        mosquitto_lib_cleanup();
        return;
    }
    printf("create mosquitto successfully!\n");

    mosquitto_message_callback_set(mosq1, vibration_message_callback);

    if(mosquitto_username_pw_set(mosq1, SERVER_USER, SERVER_PASSWORD) != MOSQ_ERR_SUCCESS){
        printf("user and passwd fail!\n");
        mosquitto_destroy(mosq1);
        mosquitto_lib_cleanup();
        return;
    }
    
    if(mosquitto_connect(mosq1, ip, port, keep_alive) != MOSQ_ERR_SUCCESS){
        printf("mosqpub_connect() failed\n");
        mosquitto_destroy(mosq1);
        mosquitto_lib_cleanup();
        return;
    }
    printf("connect %s:%d successfully!\n", ip, port);

    int loop = mosquitto_loop_start(mosq1);
    if(loop != MOSQ_ERR_SUCCESS){
        printf("mosquitto loop error\n");
        mosquitto_destroy(mosq1);
        mosquitto_lib_cleanup();
        return;
    }

}

void vibration_publish(char *topic, uint8_t *payload)
{
    int mid = 123;

    if(mosquitto_publish(mosq1, &mid, topic, 32, payload, 1, 0) != MOSQ_ERR_SUCCESS){
        printf("mqttpub_publish() error\n");
        mosquitto_destroy(mosq1);
        mosquitto_lib_cleanup();
        return;
    }
    else
    {
        printf("publish qos1 success!\n\n");
    }
}

void vibration_subcribe(char *topic)
{
    //struct mosquitto *mosq = NULL;
    //running = 1;

    if(mosquitto_subscribe(mosq1, NULL, topic, 1) != MOSQ_ERR_SUCCESS){
        printf("mqttsub_test() error\n");
        mosquitto_destroy(mosq1);
        mosquitto_lib_cleanup();
        return;
    }
    else
    {
        printf("subcribe qos1 success!\n");
        running = 1;
    }
/*
    while(1)
    {
        sleep(1);
    }
    */
}

void vibration_message_callback(struct mosquitto *mosq1, void *obj, const struct mosquitto_message *msg)
{
    printf("receive a message of %s: ", (char *)msg->topic);
    
    if(strcmp((char *)msg->topic, SERVER_REGSUB) == 0){

        RegSub_t RegSub_temp;

        memcpy(RegSub_temp.byte_type, msg->payload, 2);
        memcpy(RegSub_temp.byte_long, msg->payload+2, 4);
        memcpy(RegSub_temp.byte_id, msg->payload+6, 8);
        memcpy(RegSub_temp.byte_auth, msg->payload+14, 2);
        //printf("start\n");

        printf("%s %d %s %d\n", RegSub_temp.type_temp, RegSub_temp.long_temp, RegSub_temp.id_temp, RegSub_temp.auth_temp);

        if((strcmp(RegSub_temp.type_temp, "rr") == 0) && (strcmp(RegSub_temp.id_temp, station_id) == 0) && RegSub_temp.auth_temp == 0){
            running = 0;
        }
    }
    //running = 0;
    //mosquitto_disconnect(mosq1);
}


void vibration_closeconn()
{
    mosquitto_disconnect(mosq1);
    mosquitto_loop_stop(mosq1, false);
    mosquitto_destroy(mosq1);
    mosquitto_lib_cleanup();
    printf("mqtt close\n");
}

/*
void my_mqtt_reg(char *topic, char *station_id, int str_long, float longitude, float latitude, float strain, float acceleration, char *mode, char *version)
{
    bool session = MQTT_SESSION;
    struct mosquitto *mosq = NULL;
    char *clientid = MQTT_CLIENTID;
    char *ip = MQTT_HOST;
    int port = MQTT_PORT;
    int keep_alive = KEEP_ALIVE;
    cJSON *head = cJSON_CreateObject();
    cJSON *load = cJSON_CreateObject();
    int mid = 123;

    printf("%s\n", topic);
    char *buf;

    cJSON_AddItemToObject(head, "method", cJSON_CreateString("thing.service.property.set"));
    cJSON_AddItemToObject(head, "id", cJSON_CreateString("10000"));
    cJSON_AddItemToObject(head, "params", load);
    cJSON_AddItemToObject(load, "ID", cJSON_CreateString(station_id));
    cJSON_AddNumberToObject(load, "longitude", longitude);
    cJSON_AddNumberToObject(load, "latitude", latitude);
    cJSON_AddNumberToObject(load, "strain", strain);
    cJSON_AddNumberToObject(load, "acceleration", acceleration);
    cJSON_AddItemToObject(load, "mode", cJSON_CreateString(mode));
    cJSON_AddItemToObject(load, "version", cJSON_CreateString(version));
    cJSON_AddItemToObject(head, "version", cJSON_CreateString("1.0.0"));    

    //sprintf(payload, "{\"method\":\"thing.service.property.set\",\"id\":\"1000000000\",\"params\":{\"ID\":\"%s\",\"longitude\":%f,\"latitude\":%f,\"strain\":%f,\"acceleration\":%f,\"mode\":\"%c\",\"version\":\"%c\"},\"version\":\"1.0.0\"}", station_id, longitude, latitude, strain, acceleration, mode, version);
    //printf("%s\n", payload);

    //cJSON * json = cJSON_Parse(payload);
    buf = cJSON_Print(head);
    printf("%s\n", buf);

    mosquitto_lib_init();
    mosq = mosquitto_new(clientid, session, NULL);

    if(!mosq){
        printf("mqttpub_connect create() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("create mosquitto successfully!\n");

    if(mosquitto_username_pw_set(mosq, MQTT_USER, MQTT_PASSWORD) != MOSQ_ERR_SUCCESS){
        printf("user and passwd fail!\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    
    if(mosquitto_connect(mosq, ip, port, keep_alive) != MOSQ_ERR_SUCCESS){
        printf("mosqpub_connect() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("connect %s:%d successfully!\n", ip, port);

    int loop = mosquitto_loop_start(mosq);
    if(loop != MOSQ_ERR_SUCCESS){
        printf("mosquitto loop error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }

    sleep(1);

    if(mosquitto_publish(mosq, &mid, topic, strlen(buf)+1, buf, 0, 0) != MOSQ_ERR_SUCCESS){
        printf("mqttpub_publish() error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    else
    {
        printf("publish qos0 success!\n\n");
    }

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    
    sleep(5);
    return;
}

void my_mqtt_pub(char *topic, char *payload)
{
    bool session = MQTT_SESSION;
    struct mosquitto *mosq = NULL;
    char *clientid = MQTT_CLIENTID;
    char *ip = MQTT_HOST;
    int port = MQTT_PORT;
    int keep_alive = KEEP_ALIVE;

    mosquitto_lib_init();
    mosq = mosquitto_new(clientid, session, NULL);

    if(!mosq){
        printf("mqttpub_connect create() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("create mosquitto successfully!\n");

    if(mosquitto_username_pw_set(mosq, MQTT_USER, MQTT_PASSWORD) != MOSQ_ERR_SUCCESS){
        printf("user and passwd fail!\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    
    if(mosquitto_connect(mosq, ip, port, keep_alive) != MOSQ_ERR_SUCCESS){
        printf("mosqpub_connect() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("connect %s:%d successfully!\n", ip, port);

    int loop = mosquitto_loop_start(mosq);
    if(loop != MOSQ_ERR_SUCCESS){
        printf("mosquitto loop error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }

    sleep(1);

    if(mosquitto_publish(mosq, NULL, topic, strlen(payload)+1, payload, 0, 0) != MOSQ_ERR_SUCCESS){
        printf("mqttpub_publish() error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    else
    {
        printf("publish qos0 success!\n\n");
    }

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    
    sleep(5);
    return;
}

void my_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
    printf("receive a message of %s: %s\n", (char *)msg->topic, (char *)msg->payload);
    running = 0;
    mosquitto_disconnect(mosq);
}

void my_mqtt_sub(char *topic)
{
    bool session = MQTT_SESSION;
    struct mosquitto *mosq = NULL;
    char *clientid = MQTT_CLIENTID;
    char *ip = MQTT_HOST;
    int port = MQTT_PORT;
    int keep_alive = KEEP_ALIVE;
    
    
    running = 1;


    mosquitto_lib_init();
    mosq = mosquitto_new(clientid, session, NULL);

    if(!mosq){
        printf("mqttsub_connect create() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("create mosquitto successfully!\n");

    mosquitto_message_callback_set(mosq, my_message_callback);

    if(mosquitto_username_pw_set(mosq, MQTT_USER, MQTT_PASSWORD) != MOSQ_ERR_SUCCESS){
        printf("user and passwd fail!\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    
    if(mosquitto_connect(mosq, ip, port, keep_alive) != MOSQ_ERR_SUCCESS){
        printf("mosqsub_connect() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("connect %s:%d successfully!\n", ip, port);

    if(mosquitto_subscribe(mosq, NULL, topic, 0) != MOSQ_ERR_SUCCESS){
        printf("mqttsub_test() error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
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
        return;
    }

    while(running){
        sleep(1);
    }

    mosquitto_loop_stop(mosq, false);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

}
*/
/*
int main()
{
    my_mqtt_pub("hellowfsdkfhshfhsfhsdahfisdifhidsfjidshfisdhaaidfhsdhkfhskfshkfljhs", MQTT_TOPIC_REG);
    my_mqtt_sub(MQTT_TOPIC_SUB);
}
*/