#ifndef __MQTT_H__
#define __MQTT_H__

void my_mqtt_reg(char *topic, char *station_id, int str_long, float longitude, float latitude, float strain, float acceleration, char mode, char version);
void my_mqtt_pub(char *payload, char *topic);
void my_mqtt_sub(char *topic);

#endif