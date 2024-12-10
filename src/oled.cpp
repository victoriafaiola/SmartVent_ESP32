#include "oled.h"


// Definir la dirección I2C para el display OLED
#define SSD1306_I2C_ADDRESS 0x3C  


// Inicializar la pantalla OLED
void oled_inicializar() {
  // Iniciar la comunicación con el display OLED
  if (!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    // Si no se puede inicializar, mostrar un mensaje en el puerto serial y seguir con el programa
    Serial.println(F("No se pudo inicializar la pantalla OLED. Continuando..."));
    return;
  }


  display.clearDisplay();  // Limpiar la pantalla al inicio
  display.setTextSize(2);  // Tamaño de texto mayor para mejor legibilidad
  display.setTextColor(SSD1306_WHITE);  // Color blanco para el texto
  display.setCursor(0, 0);  // Posición inicial del texto
  display.display();  // Actualizar la pantalla
}


// Mostrar los valores en la pantalla OLED
void oled_mostrar_datos(float temperatura, float humedad, bool ventilador_estado) {
  display.clearDisplay();  // Limpiar la pantalla antes de actualizar los datos
  display.setCursor(0, 0);  // Posición inicial del texto


  // Mostrar la temperatura
  display.print("Temp: ");
  display.print(temperatura);
  display.println(" C");


  // Mostrar la humedad
  display.print("Humedad: ");
  display.print(humedad);
  display.println(" %");


  // Mostrar el estado del ventilador
  display.print("Ventilador: ");
  if (ventilador_estado) {
    display.println("ON");
  } else {
    display.println("OFF");
  }


  display.display();  // Actualizar la pantalla con la nueva información
}
