#include "rele.h"


// Inicializa el relé
void rele_inicializar() {
  pinMode(RELE_PIN, OUTPUT);  // Configura el pin del relé como salida
  digitalWrite(RELE_PIN, LOW); // Asegura que el ventilador esté apagado al inicio
}


// Activa el ventilador
void rele_on() {
  digitalWrite(RELE_PIN, HIGH); // Enciende el ventilador
}


// Apaga el ventilador
void rele_off() {
  digitalWrite(RELE_PIN, LOW); // Apaga el ventilador
}
