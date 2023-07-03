#ifndef MQTT_H
#define MQTT_H

void messageHandler(char* topic, byte* payload, unsigned int length);

void mqttsetup();

void dangercontrol();

void publishMessage(String isFinger, String BPM, String RotX, String RotY, String RotZ, String AccX, String AccY, String AccZ);

void mqttloop();


#endif
