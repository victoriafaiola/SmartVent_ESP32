#include "measures.h"
#include "config.h"
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
 
#define NUM_AVERAGE_OBJECTS 2
#define WINDOW_SIZE         60

//Local variables
uint32_t msec_an_reg;
uint32_t msec_an_sample;
uint8_t sample=0;

//Extern variables
extern Config config;

//Data array with variables to measure
Data data[] = {
    // name, raw_value, inst_value, ave_value, sd_value, max_value, min_value, sensor, type, pin
    "Temperature", TEMPERATURE, 0, 0, 0, 0, 0, 0, DHT11_SENSOR, ANALOG_VAR, SENSOR_PIN,0,
    "Humidity", HUMIDITY, 0, 0, 0, 0, 0, 0, DHT11_SENSOR, ANALOG_VAR, SENSOR_PIN,0
};
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
  bool procesed;

//Calculate number of variables in Data Structure
const uint8_t numberOfVars = sizeof(data) / sizeof(data[0]);

//Create temp_proc objet to calculate average, max, min & sd for temperature readings
Average<float>* array_proc[NUM_AVERAGE_OBJECTS];


//--Public functions


void measure_init(void){
    msec_an_reg=millis();
    msec_an_sample=millis();
    Serial.println(numberOfVars);
        for (int i = 0; i < NUM_AVERAGE_OBJECTS; i++) {
        array_proc[i] = new Average<float>(WINDOW_SIZE);
    }
}

uint8_t measure_count(void){
    return numberOfVars;
}

Data * measure_loop(void){
    if((millis()-msec_an_sample)>=MAX_mSEC_SAMPLE_MEASURE){
        #ifdef DEBUG_MEAS
            Serial.print("[DEBUG] Take a sample:");
            sample++;
            Serial.println(sample);
        #endif

        _measure_read_sensor();
        msec_an_sample=millis();
    }
    if((millis()-msec_an_reg)>=MAX_mSEC_AVE_MEASURE){
        #ifdef DEBUG_MEAS
            Serial.println("[DEBUG] Process...");
            sample=0;
        #endif
        for (uint8_t var_idx=0;var_idx<numberOfVars;var_idx++){
            if(data[var_idx].type==ANALOG_VAR){
                data[var_idx].ave_value=array_proc[var_idx]->mean();
                data[var_idx].ave_value=array_proc[var_idx]->mean();
                data[var_idx].sd_value=array_proc[var_idx]->stddev();
                data[var_idx].max_value=array_proc[var_idx]->maximum();
                data[var_idx].min_value=array_proc[var_idx]->minimum();        
                data[var_idx].processed=true;
                msec_an_reg=millis();
            
                #ifdef DEBUG_MEAS
                    Serial.printf("[DEBUG] %s: inst:%3.1f ave:%3.1f sd:%3.1f max:%3.1f min:%3.1f\r\n",data[var_idx].name,\
                        data[var_idx].inst_value,\
                        data[var_idx].ave_value, \
                        data[var_idx].sd_value, \
                        data[var_idx].max_value, \
                        data[var_idx].min_value);
                #endif
            }
        }
    }
    return data;
}

//Private functions

void _measure_read_sensor(void){
    for (uint8_t var_idx=0;var_idx<numberOfVars;var_idx++){
        if(data[var_idx].type==ONBOARD_LED_PIN){
            switch(data[var_idx].variable){
                case TEMPERATURE:
                    data[var_idx].raw_value = analogRead(data[var_idx].pin);
                    data[var_idx].inst_value = _measure_unit_calc(var_idx, data[var_idx].sensor);
                    array_proc[TEMPERATURE]->push(data[var_idx].inst_value);                   
                    break;
                case HUMIDITY:
                    data[var_idx].raw_value = analogRead(data[var_idx].pin);
                    data[var_idx].inst_value = _measure_unit_calc(var_idx, data[var_idx].sensor);
                    array_proc[HUMIDITY]->push(data[var_idx].inst_value);                   
                    break;

            }
        }
    }
}


float _measure_unit_calc(uint8_t var_idx, uint16_t unit){
    float value=0;
    switch (unit){
        case DHT11:
            value=data[var_idx].raw_value;
            break;
    }
    return value;
}