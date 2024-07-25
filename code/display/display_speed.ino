#include <U8g2lib.h>

// Create an instance of the U8g2 class for an SSD1306-based OLED display
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

float speedKmH = 50.0; 
//const int speedPin = D7


float kmhToMph(float kmh) {
  return kmh * 0.621371; 
}

void setup(void) {
  u8g2.begin(); 
  // pinMode(speedPin, INPUT); 
}

void loop(void) {
  float speedMph = kmhToMph(speedKmH);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_tom_thumb_4x6_mf);
  u8g2.setCursor(0, 20);
  u8g2.print("Speed: ");

  u8g2.setFont(u8g2_font_ncenB24_tr);
  u8g2.setCursor(30, 40);
  u8g2.print(speedKmH, 0);

  u8g2.setFont(u8g2_font_tom_thumb_4x6_mf);
  u8g2.setCursor(30, 60);
  u8g2.print(" km/h");


  u8g2.setFont(u8g2_font_fub20_tr);
  u8g2.setCursor(80, 40);
  u8g2.print(speedMph, 0);

  u8g2.setFont(u8g2_font_tom_thumb_4x6_mf);
  u8g2.setCursor(80, 60);
  u8g2.print(" mph");

  // Send the buffer to the display
  u8g2.sendBuffer();

  // Delay to avoid flickering
  delay(1000);
}


