#include "oled.h"

//--Instances
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_SCL_PIN, OLED_SDA_PIN);
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];
U8X8LOG u8x8log;

//--Local variables
uint32_t start_clock=millis();

//--extern variables
extern float temperature;
extern float humidity;
extern float fan;

//-Definitions screen area tittle
areaScreen areaTittle = {
  0,8,128,20
};

//-Definitions screen area values
areaScreen areaV = {
0,20,128,70
};


void oled88_init(void){
  Wire.begin(OLED_SDA_PIN,OLED_SCL_PIN);
  u8g2.begin();
  u8x8log.begin(U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);
  u8x8log.setRedrawMode(1);		//--  0: Update screen with newline, 1: Update screen for every char  
  u8g2.setFlipMode(1);        //--  rotate screen 180 degrees

}

void oled88_test(void){
  u8g2.setDrawColor(1);
  u8g2.drawBox(0,0,128,64);
  u8g2.sendBuffer();
  u8g2.setDrawColor(0);
  for(int r=0; r<128; r++){
    u8g2.drawBox(r,0,r+1,64);
    u8g2.sendBuffer();
  }
  u8g2.setDrawColor(1);
}

void oled88_clear(void){
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}

void oled88_bienvenida(void){
  u8g2.setMaxClipWindow();
  u8g2.setFont(u8g2_font_spleen6x12_mf);
  u8g2.setCursor(10,35);
  u8g2.print("SmartVent_ESP32");
  u8g2.setFont(u8g2_font_streamline_all_t); 
  u8g2.sendBuffer();
  delay(5000);
}

void oled88_update(void){
if ((millis()-start_clock)>=5000){
      start_clock=millis();
      oled88_printTit(" Measures:        ");
      oled88_printV(temperature,humidity,fan);      
    }
    delay(10);
}

//--Print message in tittle area
void oled88_printTit(const char * tittle){
  u8g2.setClipWindow(areaTittle.xorg,areaTittle.yorg,areaTittle.xend,areaTittle.yend);
  u8g2.setFont(u8g2_font_spleen6x12_mf);//u8g2_font_helvB08_tr);
  u8g2.setCursor(0, 18);
  u8g2.print(tittle);
  u8g2.sendBuffer();
}

//--Print 3 values in value area
void oled88_printV(float value1,float value2,float value3){
    //u8x8.setFont(u8g2_font_9x15_t_cyrillic);
    u8g2.setClipWindow(areaV.xorg,areaV.yorg,areaV.xend,areaV.yend);
    u8g2.setFont(u8g2_font_spleen6x12_mf);
    u8g2.setCursor(0, 30);
    u8g2.printf(" Temperature:%3.1f C ",value1);
    u8g2.setCursor(0, 40);
    u8g2.printf(" Humidity:%3.1f RH ",value2);
    u8g2.setCursor(0, 50);
    u8g2.printf(" Fan: %s ", fan ? "ON" : "OFF");
    u8g2.sendBuffer();
}