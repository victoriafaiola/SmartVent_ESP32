#ifndef WIFI_H
#define WIFI_H

//--Includes
#include <Arduino.h>
#include <WiFi.h>
#include "config.h" 
#include "setup.h" 
#include <WiFiType.h>

//--Timeouts for reconnection and connection waiting (20 seconds)
#define RECONN_TIMEOUT              20000     
#define WAITFORCONNECT_TIMEOUT      20000     

//--WiFi connection states for FSM (Finite State Machine)
enum FSM_WIFI_STATES {
    DISCONNECTED,    
    CONNECTED,       
    RECONNECT,       
    WAITTORECONNECT, 
    WAITFORCONNECT   
};

//--Prototypes
bool wifi_init(WiFiMode_t mode);
bool wifi_loop(void);

//--Privates prototypes
bool _connect(void);
void _FSM_state_led(uint8_t __wifi_state, uint8_t led);
uint8_t _get_wifi_status(void);
void _APconnect(void);

#endif 
