#ifndef MQTT_H
#define MQTT_H


#include <WiFi.h>
#include <PubSubClient.h>  // Librería para MQTT


// Definir las credenciales de WiFi y el broker MQTT
#define WIFI_SSID "TU_RED_WIFI"
#define WIFI_PASSWORD "TU_CONTRASEÑA_WIFI"
#define MQTT_SERVER "BROKER_MQTT"  


// Configuración de la conexión WiFi y MQTT
void conectar_wifi();
void conectar_mqtt();
void reconectar_mqtt();


// Publicar los datos de temperatura, humedad y estado del ventilador
void publicar_datos(float temperatura, float humedad, bool ventilador_estado);


// Inicialización de la conexión MQTT
extern WiFiClient espClient;
extern PubSubClient client;


#endif 