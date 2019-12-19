/*
 * nodered.c
 *
 *  Created on: 2 déc. 2019
 *      Author: bdosd
 */


//http://homecontrol:1880/mqtt?topic=

#define MQTT_BROKER "http://homecontrol:1880/"

int nodered_publish(char* topic, char* value)
{
	char cmdline[1024];
	sprintf(cmdline, "wget -q -O temp.mqtt \"%smqtt?topic=%s&payload=%s\"",MQTT_BROKER, topic, value);
	system(cmdline);
}
