//Includes
#include "app.h"
#include "publish.h"

//Local variables
bool mqtt_state=0;
extern bool wifi_state;

//Main application
void App_loop(void){
    wifi_state=wifi_loop();
    mqtt_state=broker_loop();
    publish_measures();
    publish_relay();
}