#ifndef MEASURES_H
#define MEASURES_H

//Includes
#include <Arduino.h>
#include <Average.h> 
#include "config.h"

//Macros
#define MAX_SEC_AVE_MEASURE     60                              
#define MAX_SEC_SAMPLE_MEASURE  1                               
#define MAX_mSEC_AVE_MEASURE    ((MAX_SEC_AVE_MEASURE) * (1000)) 
#define MAX_mSEC_SAMPLE_MEASURE ((MAX_SEC_SAMPLE_MEASURE) * (1000)) 
#define SAMPLES_COUNT           MAX_SEC_AVE_MEASURE / MAX_SEC_SAMPLE_MEASURE

#define DEBUG_MEASURES //For debug purposes

//Enumeration for sensors
enum sensor_type {
    DHT11_SENSOR = 0
};

//Enumeration for types of variables
enum var_type {
    ANALOG_VAR = 0,
    DIGITAL_VAR
};

//Enumeration for variable position in data structure
enum var_pos {
    TEMPERATURE = 0,
    HUMIDITY
};

//Structures for measured variables
struct Data {
    const char* name;
    uint8_t variable;
    uint16_t raw_value;
    float inst_value;
    float ave_value;
    float sd_value;
    float max_value;
    float min_value;
    uint8_t sensor;
    uint8_t type;
    uint8_t pin;
    bool processed;
};

//Public prototypes
void measures_init(void);
uint8_t measures_count(void);
Data* measures_loop(void);

//Private prototypes
void measures_read_sensor(void);
float measures_unit_calc(uint8_t reg_idx, uint16_t unit);

#endif
