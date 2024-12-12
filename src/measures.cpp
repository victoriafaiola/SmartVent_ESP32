#include "measures.h"
#include "config.h"
#include <DHT.h>

//--Inicializates sensor
DHT dht(SENSOR_PIN, DHT11);

//--Inicializates measures
void measures_init(void) {
    dht.begin();
}

//--Define measures
Data measures[2] = {
    {"temperature", 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, SENSOR_PIN, 0, true},
    {"humidity", 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, SENSOR_PIN, 1, true}
};

//--Read measures
Data* measures_loop(void) {
    measures[0].inst_value = dht.readTemperature();
    measures[1].inst_value = dht.readHumidity();

    return measures;
}
