#ifndef CONFIG_H
#define CONFIG_H

//Includes
#include <Arduino.h>

//Hardware pins

//Sensor pin
#define SENSOR_PIN                 2

//Relay pin
#define RELAY_PIN                  13

//Oled pins
#define OLED_SCL_PIN               22
#define OLED_SDA_PIN               23

//Led pin
#define ONBOARD_LED_PIN            5  

//Software constants
#define SERIAL_BAUDRATE             19200

//Structures
struct Config {
  const char* device;
  const char* ssid;
  const char* ssid_pass;
  const char* ap_ssid;
  const char* ap_pass;
  const char* mqtt_server;
  uint16_t mqtt_tcp;
  uint8_t irr_hour;
  uint8_t irr_minute;
  uint8_t irr_time;
};

#endif
