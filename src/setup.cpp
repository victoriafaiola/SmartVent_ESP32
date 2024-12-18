//Includes
#include "setup.h"

//Local variables
uint8_t var_count;
extern bool wifi_state;
Config config;


//Startup function
void App_setup(void){
    Serial.begin(SERIAL_BAUDRATE);

    //PINS
    pinMode(ONBOARD_LED_PIN,OUTPUT);

    //Load stored variables
    load_config();

    //Init wifi
    wifi_state=wifi_init(WIFI_STA);


    //Presentation
    Serial.println("\r\nCátedra de Electrónica II UTN-FRRO");
    Serial.println("Persist variables");

    //Read command configuration
    conf_read();
}