#include "mqtt.h"
#include "wifi.h"
#include "config.h"
#include <PubSubClient.h>
#include <WiFi.h>

WiFiClient espClient;
PubSubClient client(espClient);

const char* mqtt_server = "IP Broker";  
const char* mqtt_user = "User";  
const char* mqtt_pass = "Password";  

//--Inicializates broker
void broker_init() {
    client.setServer(mqtt_server, 1883);  
    client.setCallback(mqtt_callback);    
}

//--Broker conection
bool broker_conn(void) {
    if (!client.connected()) {
        while (!client.connected()) {
            Serial.print("Conect to MQTT...");
            if (client.connect("SmartVent", mqtt_user, mqtt_pass)) {
                Serial.println("Conected");
                client.subscribe("smartvent/commands");  
            } else {
                Serial.print("Try to reconect...");
                delay(5000);
            }
        }
    }
    return client.connected();
}

//--Publish
bool broker_pub(const char* topic, const char* message) {
    return client.publish(topic, message);  
}

// Función de callback para recibir mensajes (si es necesario)
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Mensaje recibido en tema: ");
    Serial.println(topic);

    if (String(topic) == "smartvent/commands") {
    }
}

// Función para mantener la conexión con el broker
void broker_loop() {
    client.loop();  
}
