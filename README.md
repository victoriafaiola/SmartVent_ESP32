# SmartVent ESP32


**SmartVent ESP32** es un proyecto de ventilación inteligente basado en el microcontrolador ESP32. El sistema utiliza un sensor de temperatura y humedad DHT11 para controlar un ventilador a través de un relé. Los datos de temperatura y humedad se muestran en una pantalla OLED y se envían a través de MQTT para su monitoreo remoto.


## Características del Proyecto


- **Microcontrolador**: ESP32
- **Sensor de temperatura y humedad**: DHT11
- **Pantalla OLED**: Visualiza los valores de temperatura, humedad y el estado del ventilador.
- **Control del ventilador**: El ventilador se enciende automáticamente cuando la temperatura supera los 25°C o la humedad es mayor a 65%.
- **Conexión Wi-Fi**: Conexión estable a una red Wi-Fi para comunicación utilizando el protocolo MQTT.
- **Plataforma de monitoreo**: Utiliza Node-RED para visualizar y analizar los datos enviados por MQTT.


## Componentes Necesarios


1. **ESP32**
2. **Sensor DHT11**
3. **Pantalla OLED 128x64**
4. **Relé de 5V**
5. **Ventilador de 5V**
6. **Cables de conexión**
7. **Fuente de alimentación de 5V**


## Instalación y Configuración


### Requisitos


- **Plataforma**: PlatformIO
- **Bibliotecas necesarias**:
  - `Adafruit Unified Sensor` (v1.1.14)
  - `Adafruit DHT sensor library` (v1.4.6)
  - `Adafruit SSD1306` (v2.5.13)
  - `Adafruit GFX Library` (v1.11.11)
  - `PubSubClient` (v2.8)


### Pasos para la instalación


1. **Configura el entorno de desarrollo**:
     1. Instala PlatformIO en VSCode.
     2. Crea un nuevo proyecto para **ESP32** con el marco **Arduino**.
   
2. **Instalar las bibliotecas necesarias**:
   En PlatformIO, agrega las bibliotecas necesarias en el archivo `platformio.ini` o en el `lib_deps`.


3. **Configura Node-RED**:
   - Configura un servidor Node-RED.
   - Añade un nodo de **MQTT** para recibir los datos enviados por el ESP32.
   - Configura el **broker MQTT** para manejar la comunicación.
   
4. **Conectar el hardware**:
   Conecta los componentes como se describe en la sección de **Conexiones** más abajo.


## Conexiones


| Componente      | Pin    | Conexión en ESP32    |
|-----------------|--------|----------------------|
| **DHT11**       | VCC    | 3.3V                 |
|                 | GND    | GND                  |
|                 | OUT    | GPIO2 (D2)           |
| **Relé**        | +      | VIN                  |
|                 | S      | GPIO13 (D13)         |
|                 | -      | GND                  |
| **Ventilador**  | +      | +5V                  |
|                 | -      | COM (Relé)           |
| **OLED**        | VCC    | 3.3V                 |
|                 | GND    | GND                  |
|                 | SDA    | GPIO23 (D23)         |
|                 | SCL    | GPIO22 (D22)         |


## Código


El código está estructurado en diferentes archivos para modularidad y facilidad de mantenimiento:


- `sensores.h` y `sensores.cpp`: Gestionan la lectura del sensor DHT11.
- `rele.h` y `rele.cpp`: Controlan el estado del relé que enciende y apaga el ventilador.
- `oled.h` y `oled.cpp`: Gestionan la pantalla OLED para mostrar los datos.
- `mqtt.h` y `mqtt.cpp`: Se encargan de la comunicación MQTT con Node-RED.


## Funcionamiento


1. **Lectura de datos**: El ESP32 lee los datos del sensor DHT11 cada 2 segundos.
2. **Control del ventilador**: Si la temperatura es mayor a 25°C o la humedad es mayor a 65%, el ventilador se activa automáticamente mediante el relé.
3. **Visualización en OLED**: Los valores de temperatura, humedad y el estado del ventilador se muestran en la pantalla OLED.
4. **Envío de datos a Node-RED**: Los datos de temperatura y humedad se envían en tiempo real a Node-RED a través de MQTT.
