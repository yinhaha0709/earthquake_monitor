#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mosquitto.h>
#include <mysql/mysql.h>
//#include <sys/reboot.h>
#include <string.h>
#include "../include/config.h"
#include "../include/database.h"
#include "../include/mqtt.h"
#include "../include/cJSON.h"

//int running;
int running, ontime_status, ftp_status, ontime_block_num;
int fd_watchdog;
char threshold_status[6];
//static unsigned char food = 0;

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

} RegSub_t;

typedef struct OntimeSub_T
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
        short ctrl_command;
        uint8_t byte_ctrl[2];
    };

    union
    {
        char ctrl_word;
        uint8_t byte_word;
    };

} OntimeSub_t;

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

    if (!mosq)
    {
        printf("mqttpub_connect create() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("create mosquitto successfully!\n");

    //mosquitto_message_callback_set(mosq, my_message_callback);

    if (mosquitto_username_pw_set(mosq, MQTT_USER, MQTT_PASSWORD) != MOSQ_ERR_SUCCESS)
    {
        printf("user and passwd fail!\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }

    if (mosquitto_connect(mosq, ip, port, keep_alive) != MOSQ_ERR_SUCCESS)
    {
        printf("mosqpub_connect() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("connect %s:%d successfully!\n", ip, port);

    int loop = mosquitto_loop_forever(mosq, 5000, 1);
    if (loop != MOSQ_ERR_SUCCESS)
    {
        printf("mosquitto loop error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
}

void my_mqtt_publish(char *topic, char *payload)
{
    int mid = 123;

    if (mosquitto_publish(mosq, &mid, topic, strlen(payload) + 1, payload, 0, 0) != MOSQ_ERR_SUCCESS)
    {
        printf("mqttpub_publish() error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    else
    {
        printf("publish qos0 success!\n\n");
        ///////////////////////////////////////////

        ///////////////////////////////////////////
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

    if (!mosq)
    {
        printf("mqttpub_connect create() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("create mosquitto successfully!\n");

    mosquitto_message_callback_set(mosq, my_message_callback);

    if (mosquitto_username_pw_set(mosq, MQTT_USER, MQTT_PASSWORD) != MOSQ_ERR_SUCCESS)
    {
        printf("user and passwd fail!\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }

    if (mosquitto_connect(mosq, ip, port, keep_alive) != MOSQ_ERR_SUCCESS)
    {
        printf("mosqpub_connect() failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    printf("connect %s:%d successfully!\n", ip, port);

    int loop = mosquitto_loop_start(mosq);
    if (loop != MOSQ_ERR_SUCCESS)
    {
        printf("mosquitto loop error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    running = 1;

    if (mosquitto_subscribe(mosq, NULL, topic, 0) != MOSQ_ERR_SUCCESS)
    {
        printf("mqttsub_test() error\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }
    else
    {
        printf("subcribe qos0 success!\n");
    }

    while (running)
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

    if (!mosq1)
    {
        printf("mqttpub_connect create() failed\n");
        mosquitto_destroy(mosq1);
        mosquitto_lib_cleanup();
        return;
    }
    printf("create mosquitto successfully!\n");

    mosquitto_publish_callback_set(mosq1, vibration_publish_callback);
    mosquitto_message_callback_set(mosq1, vibration_message_callback);

    if (mosquitto_username_pw_set(mosq1, SERVER_USER, SERVER_PASSWORD) != MOSQ_ERR_SUCCESS)
    {
        printf("user and passwd fail!\n");
        mosquitto_destroy(mosq1);
        mosquitto_lib_cleanup();
        return;
    }

    if (mosquitto_connect(mosq1, ip, port, keep_alive) != MOSQ_ERR_SUCCESS)
    {
        printf("mosq_connect() failed\n");
        mosquitto_destroy(mosq1);
        mosquitto_lib_cleanup();
        exit(0);
    }
    printf("connect %s:%d successfully!\n", ip, port);

    int loop = mosquitto_loop_start(mosq1);
    if (loop != MOSQ_ERR_SUCCESS)
    {
        printf("mosquitto loop error\n");
        mosquitto_destroy(mosq1);
        mosquitto_lib_cleanup();
        return;
    }
}

void vibration_publish(char *topic, uint8_t *payload, int byte_size)
{
    int mid = 123;

    if (mosquitto_publish(mosq1, &mid, topic, byte_size, payload, 1, 0) != MOSQ_ERR_SUCCESS)
    {
        printf("mqttpub error\n");
        mosquitto_destroy(mosq1);
        mosquitto_lib_cleanup();
        return;
    }
    else
    {
        printf("publish qos1 start!\n\n");
        ///////////////////////////////////////////

        ///////////////////////////////////////////
    }
}

void vibration_subcribe(char *topic, int qos)
{
    //struct mosquitto *mosq = NULL;
    //running = 1;

    if (mosquitto_subscribe(mosq1, NULL, topic, qos) != MOSQ_ERR_SUCCESS)
    {
        printf("mqttsub error\n");
        mosquitto_destroy(mosq1);
        mosquitto_lib_cleanup();
        exit(0);
    }
    else
    {
        printf("subcribe success!\n");
        running = 1;
    }
    /*
    while(1)
    {
        sleep(1);
    }
*/
}

void vibration_publish_callback(struct mosquitto *mosq1, void *obj, int mid)
{
    printf("publish finish\n");
    //ssize_t eaten = write(fd_watchdog, &food, 1);
}

void vibration_message_callback(struct mosquitto *mosq1, void *obj, const struct mosquitto_message *msg)
{
    //printf("get\n");
    printf("receive a message of %s: ", (char *)msg->topic);

    if (strcmp((char *)msg->topic, topic_regsub) == 0)
    {

        RegSub_t RegSub_temp;

        memcpy(RegSub_temp.byte_type, msg->payload, 2);
        memcpy(RegSub_temp.byte_long, msg->payload + 2, 4);
        memcpy(RegSub_temp.byte_id, msg->payload + 6, 8);
        memcpy(RegSub_temp.byte_auth, msg->payload + 14, 2);
        //printf("start\n");

        printf("%s %d %s %d\n", RegSub_temp.type_temp, RegSub_temp.long_temp, RegSub_temp.id_temp, RegSub_temp.auth_temp);

        //printf("%d %d %d\n", strncmp(RegSub_temp.type_temp, "rr", 2), strncmp(RegSub_temp.id_temp, station_id, 8), RegSub_temp.auth_temp);

        if ((strncmp(RegSub_temp.type_temp, "rr", 2) == 0) && (strncmp(RegSub_temp.id_temp, station_id, 8) == 0) && RegSub_temp.auth_temp == 0)
        {
            running = 0;
        }
    }
    //running = 0;
    //mosquitto_disconnect(mosq1);

    if (strcmp((char *)msg->topic, topic_ontimesub) == 0)
    {

        OntimeSub_t OntimeSub_temp;
        int i = 0;

        memcpy(OntimeSub_temp.byte_type, msg->payload, 2);
        memcpy(OntimeSub_temp.byte_long, msg->payload + 2, 4);
        memcpy(OntimeSub_temp.byte_id, msg->payload + 6, 8);
        memcpy(OntimeSub_temp.byte_ctrl, msg->payload + 14, 2);
        memcpy(&OntimeSub_temp.byte_word, msg->payload + 16, 1);

        printf("%s %d %s %d %c\n", OntimeSub_temp.type_temp, OntimeSub_temp.long_temp, OntimeSub_temp.id_temp, OntimeSub_temp.ctrl_command, OntimeSub_temp.ctrl_word);

        if ((strncmp(OntimeSub_temp.type_temp, "cc", 2) == 0) && (strncmp(OntimeSub_temp.id_temp, station_id, 8) == 0))
        {
            //printf("round 1\n");
            if (OntimeSub_temp.ctrl_command == 1)
            {

                MYSQL *mysql;

                mysql = mysql_init(NULL);
                if (!mysql)
                {
                    printf("\nMysql init failed.\n");
                }

                mysqldb_connect(mysql);

                //printf("type 1\n");
                if (OntimeSub_temp.ctrl_word == 0)
                {
                    ontime_status = 0;
                    mysqldb_update(mysql, MESSAGE_INT, ontime_status, 1);
                    ontime_block_num = 0;
                    //printf("status 1-0\n");
                }
                else if (OntimeSub_temp.ctrl_word == 1)
                {
                    ontime_status = 1;
                    mysqldb_update(mysql, MESSAGE_INT, ontime_status, 1);
                    //printf("status1-1\n");
                    for (i = 0; i < 6; i++)
                    {
                        threshold_status[i] = 0;
                    }
                }

                close_connection(mysql);
                //mysql_library_end();
            }
            else if (OntimeSub_temp.ctrl_command == 2)
            {
                MYSQL *mysql;
                //printf("type 2\n");
                mysql = mysql_init(NULL);
                if (!mysql)
                {
                    printf("\nMysql init failed.\n");
                }

                mysqldb_connect(mysql);

                if (OntimeSub_temp.ctrl_word == 0)
                {
                    //printf("status 2-0\n");
                    ftp_status = 0;
                    mysqldb_update(mysql, MESSAGE_INT, ftp_status, 2);
                }
                else if (OntimeSub_temp.ctrl_word == 1)
                {
                    //printf("status 2-1\n");
                    ftp_status = 1;
                    mysqldb_update(mysql, MESSAGE_INT, ftp_status, 2);
                }

                close_connection(mysql);
                //mysql_library_end();
            }
            else if (OntimeSub_temp.ctrl_command == 3)
            {
                sync();
                vibration_closeconn();
                close(fd_watchdog);
                system("reboot");
            }
        }
    }

    printf("\n");

    fflush(stdout);
}

void vibration_closeconn()
{
    mosquitto_disconnect(mosq1);
    mosquitto_loop_stop(mosq, false);
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