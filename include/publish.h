#ifndef PUBLISH_H
#define PUBLISH_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "mqtt.h"
#include "config.h"
#include "setup.h"


#define PUBLISH_INTERVAL 10000

//Prototypes
void publish_measures(void);
void publish_relay(void);

#endif