#include <TinyGPS++.h> //1.0.3
#include <SoftwareSerial.h>
#include <U8glib.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

#define tx 10 // gps module tx pin to nano d10 pin
#define rx 11
TinyGPSPlus gps;
SoftwareSerial gpsSerial(tx, rx);

String month, day;
String hour, minute;
int offsetHour = 3;


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
      if (gps.time.isUpdated() && gps.time.isValid()) {
        day = String(gps.date.day());
        month = String(gps.date.month());
        hour = String(gps.time.hour() + offsetHour);
        hour = (hour.length() == 1) ? "0"+hour : hour;
        minute = String(gps.time.minute());
        minute= (minute.length() == 1) ? "0"+minute : minute;

        Serial.print(day);
        Serial.print("\n");
        Serial.print(hour);
        Serial.print(" : ");
        Serial.print(minute);
      }
  }
}

void update(){
    u8g.setPrintPos(0,20); // Col, Row
    u8g.print(day);
    u8g.print("/");
    u8g.print(month);
    u8g.setPrintPos(20,45); 
    u8g.print(hour);
    u8g.print(":");
    u8g.print(minute);
}


void setup(void) {
  gpsSerial.begin(9600);
  u8g.setFont(u8g_font_helvB18);
  Serial.begin(9600);
}

void loop(void) {
  readGPS();
  u8g.firstPage(); 
  do {             
    update();
  } while( u8g.nextPage() );
}
