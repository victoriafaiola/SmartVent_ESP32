#include "mqtt.h"


WiFiClient espClient;
PubSubClient client(espClient);


void conectar_wifi() {
  Serial.print("Conectando a WiFi..."); // Conexión al WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a WiFi!");
}


void conectar_mqtt() {
  client.setServer(MQTT_SERVER, 1883);  // Conexión al broker MQTT
  while (!client.connected()) {
    Serial.print("Conectando a MQTT...");
    if (client.connect("ESP32_Client")) {
      Serial.println("Conectado a MQTT");
    } else {
      Serial.print("Error de conexión, reintentando...");
      delay(5000);
    }
  }
}


void reconectar_mqtt() {
  if (!client.connected()) {
    conectar_mqtt();
  }
  client.loop();
}


void publicar_datos(float temperatura, float humedad, bool ventilador_estado) {
  if (!client.connected()) {
    reconectar_mqtt();
  }
  client.loop();


  // Publicar datos de temperatura, humedad y estado del ventilador en MQTT
  char temp_str[8];
  dtostrf(temperatura, 1, 2, temp_str);
  client.publish("home/temperature", temp_str);


  char hum_str[8];
  dtostrf(humedad, 1, 2, hum_str);
  client.publish("home/humidity", hum_str);


  client.publish("home/fan", ventilador_estado ? "ON" : "OFF");