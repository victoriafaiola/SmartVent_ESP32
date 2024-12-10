#ifndef OLED_H
#define OLED_H


#include <Arduino.h>
#include <Wire.h>         // Biblioteca para comunicación I2C
#include <Adafruit_SSD1306.h> // Biblioteca para controlar el display OLED


// Definir el tamaño de la pantalla OLED
#define OLED_WIDTH 128
#define OLED_HEIGHT 64


// Definir el pin de comunicación I2C (si es necesario)
#define OLED_RESET    -1  
#define OLED_SDA_PIN   23 // SDA está en GPIO23
#define OLED_SCL_PIN   22 // SCL está en GPIO22


// Inicializar pantalla OLED
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);


// Función para inicializar la pantalla OLED
void oled_inicializar();


// Función para mostrar los valores en la pantalla OLED
void oled_mostrar_datos(float temperatura, float humedad, bool ventilador_estado);


#endif
