#ifndef __MQTT_H__
#define __MQTT_H__

#include <mosquitto.h>

void my_mqtt_connect();
void my_mqtt_publish(char *topic, char *payload);
void my_mqtt_subcribe(char *topic);
void my_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);
void my_mqtt_closeconn();

void vibration_mqtt_connect();
void vibration_publish(char *topic, char *payload);
void vibration_subcribe(char *topic);
void vibration_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);
void vibration_closeconn();
/*
void my_mqtt_reg(char *topic, char *station_id, int str_long, float longitude, float latitude, float strain, float acceleration, char *mode, char *version);
void my_mqtt_pub(char *payload, char *topic);
void my_mqtt_sub(char *topic);
*/

#endif