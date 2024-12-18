#ifndef COMMANDS_H
#define COMMANDS_H

#include <Arduino.h>
#include <ArduinoJson.h>

void rpc_proc(char* topic, byte* payload, unsigned int length);

#endif