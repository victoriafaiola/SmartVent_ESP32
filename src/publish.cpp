#include "publish.h"

//Extern variables
extern const char * topic_telemetry;
extern Config config;

//Local variables
uint8_t flag_push=0;
uint8_t flag_push_att=1;
unsigned long long ts;
uint32_t start_clock;

void publish_measures(){
    StaticJsonDocument<200> pub;
    char json_pub[200];
    bool rc_pub=0;
    if (millis()-start_clock>=PUBLISH_INTERVAL){
        start_clock=millis();
        pub.clear();
        pub["Name"]=config.device;
        serializeJson(pub, json_pub);
        rc_pub=broker_pub(topic_telemetry,json_pub);
        if(rc_pub){
            Serial.print(F("Telemetry published:"));
            Serial.println(json_pub);
        }else{
            Serial.print(F("Telemetry not published!:"));
            Serial.println(json_pub);
        }
    }
}

void publish_relay(){
    StaticJsonDocument<200> pub;
    char json_pub[200];
    bool rc_pub=0;
    if (millis()-start_clock>=PUBLISH_INTERVAL){
        start_clock=millis();
        pub.clear();
        pub["Name"]=config.device;
        serializeJson(pub, json_pub);
        rc_pub=broker_pub(topic_telemetry,json_pub);
        if(rc_pub){
            Serial.print(F("Telemetry published:"));
            Serial.println(json_pub);
        }else{
            Serial.print(F("Telemetry not published!:"));
            Serial.println(json_pub);
        }
    }
}