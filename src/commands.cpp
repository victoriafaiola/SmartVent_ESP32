#include "commands.h"

const char* parameters;
const char* command;
StaticJsonDocument<200> payload_json;
String topic_str;
String payload_str;

void rpc_proc(char* topic, byte* payload, unsigned int length){
    topic_str=String((char*)topic);
    payload_str=String((char*)payload);
    deserializeJson(payload_json,payload_str);
    command=payload_json["method"];
    parameters=payload_json["params"];

    Serial.println(command);
    Serial.println(parameters);
}