#include <Arduino.h>
#include "sensores.h"
#include "rele.h"
#include "oled.h"
#include "mqtt.h"


// Límites de temperatura y humedad
const float LIMITE_TEMPERATURA = 25.0;
const float LIMITE_HUMEDAD = 65.0;


void setup() {
  Serial.begin(115200);
 
  // Inicializar los módulos
  sensores_inicializar();
  rele_inicializar();
  oled_inicializar();
  conectar_wifi();  
  conectar_mqtt();  
}


void loop() {
  // Leer los valores de temperatura y humedad
  float temperatura = sensor_temperatura();
  float humedad = sensor_humedad();
 
  // Comprobar si los datos son válidos
  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error al leer los datos");
    oled_mostrar_datos(0, 0, false);  // Mostrar error en OLED
  } else {
    bool ventilador_estado = false;


    // Activar el ventilador si se superan los límites
    if (temperatura > LIMITE_TEMPERATURA || humedad > LIMITE_HUMEDAD) {
      rele_on();
      ventilador_estado = true;
    } else {
      rele_off();
      ventilador_estado = false;
    }


    // Mostrar los datos por el puerto serial
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" °C, Humedad: ");
    Serial.print(humedad);
    Serial.print(" %, Ventilador: ");
    Serial.println(ventilador_estado ? "ON" : "OFF");


    // Mostrar en OLED
    oled_mostrar_datos(temperatura, humedad, ventilador_estado);


    // Publicar los datos en el broker MQTT
    publicar_datos(temperatura, humedad, ventilador_estado);
  }


  delay(2000);  // Esperar antes de la siguiente iteración
}
