#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include "app.h"
#include "cert.h"
#include "commands.h"
#include "config.h"
#include "functions.h"
#include "internet.h"
#include "measures.h"
#include "mqtt.h"
#include "oled.h"
#include "persist.h"
#include "publish.h"
#include "relay.h"
#include "setup.h"


// Variables
int maxTemp = 25;       // Temperature limit default
int maxHumidity = 65;   // Humidity limit default
bool fanState = false;  // Fan state default (off)

// Principal function
/*void control_fan(int TEMPERATURE, int HUMIDITY) {
    if (TEMPERATURE > maxTemp || HUMIDITY > maxHumidity) {
        relay_on(); 
        Serial.println("Fan on"); 
    }
    else {
        relay_off(); 
        Serial.println("Fan off"); 
    }
}*/

void setup() {
    measure_init();
    relay_init();
    oled88_init();
    wifi_init(WIFI_STA);
    publish_measures();
    publish_relay();
}

void loop(void){
        if (TEMPERATURE > maxTemp || HUMIDITY > maxHumidity) {
        relay_on(); 
        Serial.println("Fan on"); 
    }
    else {
        relay_off(); 
        Serial.println("Fan off"); 
    }
}