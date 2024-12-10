#include "sensores.h"


// Crea el objeto DHT con el pin y tipo de sensor
DHT dht(DHTPIN, DHTTYPE);


// Inicializa el sensor DHT11
void sensores_inicializar() {
  dht.begin();
}


// Obtiene la temperatura desde el DHT11
float sensor_temperatura() {
  return dht.readTemperature();  // Devuelve la temperatura en grados Celsius
}


// Obtiene la humedad desde el DHT11
float sensor_humedad() {
  return dht.readHumidity();  // Devuelve la humedad en porcentaje
}
