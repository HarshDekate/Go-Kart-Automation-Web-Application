#ifndef MQTT_H
#define MQTT_H

// void messageHandler(char* topic, byte* payload, unsigned int length);

void mqttsetup();

void dangercontrol();

void publishMessage();

void loopmqtt();


#endif
