#ifndef MQTT_H
#define MQTT_H

//Includes
#include <Arduino.h>
#include <PubSubClient.h>
#include <LittleFS.h>
#include "setup.h"
#include "internet.h"
#include "cert.h"


#define RECONN_MQTT_TIMEOUT              20000      
#define WAITFORCONNECT_MQTT_TIMEOUT      20000     
#define DELAY_PUB_MQTT_LED               20         
#define MAX_RECONN                       15

enum FSM_MQTT_STATES {
    _MQTT_DISCONNECTED,
    _MQTT_CONNECTED,
    _MQTT_RECONNECT,
    _MQTT_WAITTORECONNECT,
    _MQTT_WAITFORCONNECT,
    _MQTT_UNAVAILABLE_CONNECTION
};


void broker_init(void);
bool broker_conn(void);
bool broker_loop(void);
bool broker_pub(const char* topic, const char* message); 
uint8_t broker_get_mqtt_status(void);
void broker_FSM_blink_led(uint8_t __mqtt_state);
bool broker_sub(const char*topic);
void rpc_proc(char* topic, byte* payload, unsigned int length);


#endif
