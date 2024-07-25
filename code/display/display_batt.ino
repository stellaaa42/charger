#include <U8g2lib.h>

// Create an instance of the U8g2 class for an SSD1306-based OLED display
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

float voltage = 5.0; 
float current = 1.50; 
//const int voltagePin = A0
//const int currentPin = A1

void setup(void) {
  u8g2.begin(); 
  // pinMode(currentPin, INPUT); 
}

void loop(void) {

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_tom_thumb_4x6_mf);
  u8g2.setCursor(0, 20);
  u8g2.print("Voltage: ");
  u8g2.setCursor(70, 20);
  u8g2.print("Current: ");
  

  u8g2.setFont(u8g2_font_ncenB24_tr);
  u8g2.setCursor(10, 50);
  u8g2.print(voltage, 1);

  u8g2.setFont(u8g2_font_tom_thumb_4x6_mf);
  u8g2.setCursor(30, 60);
  u8g2.print(" V");


  u8g2.setFont(u8g2_font_fub20_tr);
  u8g2.setCursor(70, 50);
  u8g2.print(current, 1);

  u8g2.setFont(u8g2_font_tom_thumb_4x6_mf);
  u8g2.setCursor(85, 60);
  u8g2.print(" A");

  // Send the buffer to the display
  u8g2.sendBuffer();

  // Delay to avoid flickering
  delay(1000);
}


