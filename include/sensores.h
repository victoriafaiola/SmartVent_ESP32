#ifndef SENSORES_H
#define SENSORES_H


#include <Arduino.h>
#include <DHT.h>


// Configuración del sensor DHT11
#define DHTPIN 2      // En GPIO2 está conectado el DHT11
#define DHTTYPE DHT11 // Tipo de sensor DHT11


// Inicializar sensor DHT11
void sensores_inicializar();


// Obtener la temperatura
float sensor_temperatura();


// Función para obtener la humedad
float sensor_humedad();


#endif
