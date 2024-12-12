#include "relay.h"
#include "config.h"

//--Inicializates relay
void relay_init() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
}

//--Fan on
void relay_on() {
    digitalWrite(RELAY_PIN, HIGH);
}

//--Fan off
void relay_off() {
    digitalWrite(RELAY_PIN, LOW);
}
