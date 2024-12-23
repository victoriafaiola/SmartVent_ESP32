#include "mqtt.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>

//Instancies
WiFiClientSecure wifi_client;    
PubSubClient mqtt(wifi_client);


//Local variables
uint32_t _FSM_mqtt_crono;
uint32_t _FSM_led_crono;
uint8_t _mqtt_conn_retrys;
bool _subscribe_status=0;
bool _conn_mqtt_status;
uint8_t _mqtt_state = _MQTT_DISCONNECTED;
uint8_t _mqtt_last_state = _MQTT_DISCONNECTED;
uint8_t _try_mqtt_reconn;
bool _flag_mqtt_reconnected=0;

//Extern variables
extern Config config;
const char * topic_telemetry;
extern const char * topic_attributes;
extern const char * topic_rpc;


void broker_init(void){
    wifi_client.setCACert(ca_cert);
    //wifi_client.setInsecure();
    mqtt.setCallback(rpc_proc);
    mqtt.setServer(config.mqtt_server, config.mqtt_tcp);
}


bool broker_conn(void){
  _FSM_mqtt_crono = millis();
  while (!mqtt.connected()) {
    if (_mqtt_conn_retrys==0){
      Serial.print(F("Try to connect to Broker MQTT ("));Serial.print(_mqtt_conn_retrys+1);Serial.print(") ");
      Serial.print(config.mqtt_server);
      Serial.print(F(":"));
      Serial.print(config.mqtt_tcp);
      Serial.print(F(" - "));
      Serial.print(config.device);
      Serial.println(F("..."));
    }
     
    _conn_mqtt_status=mqtt.connect(config.device, config.device,""); 
    _mqtt_conn_retrys++;
    if (_conn_mqtt_status) {
        _mqtt_conn_retrys=0;
        Serial.println(F("Connected to MQTT"));
        broker_sub(topic_rpc);
        broker_sub(topic_attributes);
        _subscribe_status=1;
        return true;
    }
    if (millis() - _FSM_mqtt_crono >= WAITFORCONNECT_MQTT_TIMEOUT){
        _mqtt_conn_retrys=0;
        Serial.print(F("Fail to connect to MQTT, "));
        Serial.print(_mqtt_conn_retrys);
        Serial.print(F(" trys. Error:"));
        Serial.println(mqtt.state());
        return false;
    }
  }
  return false;
}


bool broker_loop(void){
  switch (_mqtt_state){
    case _MQTT_CONNECTED:
      if (broker_get_mqtt_status()!=_MQTT_CONNECTED){
        _mqtt_state=_MQTT_DISCONNECTED;
      }
      if (!_subscribe_status){
        broker_sub(topic_rpc);
        broker_sub(topic_attributes );
        _subscribe_status=1;
      }
      mqtt.loop();
      break;

    case _MQTT_RECONNECT:
        _subscribe_status=0;
        Serial.print(F("MQTT reconnect "));
        Serial.println(_try_mqtt_reconn);
        _try_mqtt_reconn++;
        mqtt.connect(config.device, config.device,"");
        _FSM_mqtt_crono = millis();
        _mqtt_state=_MQTT_WAITFORCONNECT;
        break;

    case _MQTT_DISCONNECTED:
        if(broker_get_mqtt_status()!=_MQTT_CONNECTED){
          _FSM_mqtt_crono = millis();
          _mqtt_state=_MQTT_RECONNECT;
          _flag_mqtt_reconnected=1;
        }else{
          _mqtt_state=_MQTT_CONNECTED;
        }
        break;

    case _MQTT_WAITTORECONNECT:
      if (millis() - _FSM_mqtt_crono >= RECONN_MQTT_TIMEOUT){
        _mqtt_state=_MQTT_RECONNECT;
      }
      break;

    case _MQTT_WAITFORCONNECT:
      if(broker_get_mqtt_status()!=_MQTT_CONNECTED){
        if (millis() - _FSM_mqtt_crono >= WAITFORCONNECT_MQTT_TIMEOUT){
          _FSM_mqtt_crono = millis();
          _mqtt_state=_MQTT_WAITTORECONNECT;
        }
      }else{
        if(_flag_mqtt_reconnected){
          Serial.println(F("MQTT reconnected!!"));
          _try_mqtt_reconn=0;
          _flag_mqtt_reconnected=0;
        }
        _mqtt_state=MQTT_CONNECTED;
      }
      break;

    default:
      break;
    
  }
  broker_FSM_blink_led(_mqtt_state);
  if (_mqtt_state==_MQTT_CONNECTED){
    return true;
  }else{
    return false;
  }
}

bool broker_pub(const char* topic, const char* message){
    if (!mqtt.connected()){
        return false;
    }
    else{
        if (mqtt.publish(topic,message)){
            return true;
        }else{
           return false;
        }
    }
}

bool broker_sub(const char* topic){
    if (!mqtt.connected()){
      Serial.println(F("Not subscribed to topic"));
      return false;
    }
    mqtt.subscribe(topic);
    return true;
}

uint8_t broker_get_mqtt_status(void){
    switch(mqtt.state()){
        case MQTT_CONNECTION_TIMEOUT:
        case MQTT_CONNECTION_LOST:
        case MQTT_CONNECT_FAILED:
        case MQTT_DISCONNECTED:
            return _MQTT_DISCONNECTED;
            break;

        case MQTT_CONNECTED:
            return _MQTT_CONNECTED;
            break;

        case MQTT_CONNECT_BAD_PROTOCOL:
        case MQTT_CONNECT_BAD_CLIENT_ID:
        case MQTT_CONNECT_UNAVAILABLE:
        case MQTT_CONNECT_BAD_CREDENTIALS:
        case MQTT_CONNECT_UNAUTHORIZED:
            return _MQTT_UNAVAILABLE_CONNECTION;
            break;
        default:
            return _MQTT_DISCONNECTED;            
    }
}

//State machine for mqtt led
void broker_FSM_blink_led(uint8_t __mqtt_state){
    uint32_t _ton;
    uint32_t _toff;
    switch (__mqtt_state){
        case _MQTT_CONNECTED:      
        _ton=30;
        _toff=2000;
        break;
        case _MQTT_DISCONNECTED:
        _ton=0;
        _toff=10000;
        break;
        case _MQTT_WAITTORECONNECT:
        _ton=30;
        _toff=30;
        break;
        case _MQTT_WAITFORCONNECT:
        _ton=200;
        _toff=200;
        break;        
        default:
        break;
    }
        _mqtt_last_state=__mqtt_state;
    }