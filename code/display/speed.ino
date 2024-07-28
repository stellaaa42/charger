#include <TinyGPS++.h> //1.0.3
#include <SoftwareSerial.h>
#include <U8glib.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);
#define tx 10 // gps module tx pin to nano d10 pin
#define rx 11 // not used
TinyGPSPlus gps;
SoftwareSerial gpsSerial(tx, rx);

double lat, lng;
int num_sat, speedKmph, speedMph;
String coord;

void readGPS(){
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (gpsSerial.available()) {
      if (gps.encode(gpsSerial.read())) {
        newData = true;
        break;
      }
    }
  }
  if(newData == true){
      newData = false;
      num_sat = gps.satellites.value();

      if (gps.location.isValid() == 1) {
        coord = gps.cardinal(gps.course.value());
        speedKmph = gps.speed.kmph();
        speedMph = gps.speed.mph();
        lat = gps.location.lat();
        lng = gps.location.lng();

        Serial.print(lat);
        Serial.print("\n");
        Serial.print(lng);
      }
  } else { 
    //no data
  }
}

void update(){
  u8g.setPrintPos(0,10); // Col, Row
  u8g.print(num_sat, 5);

  u8g.setPrintPos(0, 40);
  u8g.print(coord);

  u8g.setPrintPos(30, 10);
  u8g.setFont(u8g_font_helvB18);
  u8g.print(speedKmph);
  u8g.setPrintPos(30, 50);
  u8g.setFont(u8g_font_04b_03br);
  u8g.print("kmph");

  u8g.setPrintPos(80, 10);
  u8g.setFont(u8g_font_fur17);
  u8g.print(speedMph);
  u8g.setPrintPos(80, 50);
  u8g.setFont(u8g_font_04b_03br);
  u8g.print("mph");

  u8g.setPrintPos(0, 60);
  u8g.print("Lat: ");
  u8g.print(lat, 2);

  u8g.setPrintPos(60, 60);
  u8g.print("Lng: ");
  u8g.print(lng, 2);

}

void setup(void) {
  gpsSerial.begin(9600);
  u8g.setFont(u8g_font_04b_03br);
  Serial.begin(9600);
}

void loop(void) {
  readGPS();
  u8g.firstPage(); 
  do {             
    update();
  } while( u8g.nextPage() );
}


