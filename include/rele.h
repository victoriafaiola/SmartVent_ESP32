#ifndef RELE_H
#define RELE_H


#include <Arduino.h>


// Definir el pin donde está conectado el relé
#define RELE_PIN 13 // S está en GPIO13


// Función para inicializar el relé
void rele_inicializar();


// Activar el ventilador
void rele_on();


// Apagar el ventilador
void rele_off();


#endif
