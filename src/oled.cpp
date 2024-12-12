#include "oled.h"
#include "measures.h"  
#include "relay.h"
#include "config.h"     

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

//--Inicializates oled
void oled88_init() {
    u8g2.begin();
}

//--Show parameters
void oled88_update() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    
    //--Show title "SmartVent"
    u8g2.drawStr(0, 10, "SmartVent");
    
    //--Show measures
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 20, "Temperature:");
    char temp[10];
    snprintf(temp, sizeof(temp), "%.1f C", measures[0].inst_value); // Temperature
    u8g2.drawStr(80, 20, temp);

    u8g2.drawStr(0, 30, "Humidity:");
    char humidity[10];
    snprintf(humidity, sizeof(humidity), "%.1f %%", measures[1].inst_value); // Humidity
    u8g2.drawStr(80, 30, humidity);

    //--Show relay state
    u8g2.drawStr(0, 40, "Fan:");
    const char* relay_status = (digitalRead(RELAY_PIN) == HIGH) ? "ON" : "OFF";
    u8g2.drawStr(80, 40, relay_status);

    //--Update status
    u8g2.sendBuffer();
}
