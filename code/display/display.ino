#include <TinyGPS++.h> //1.0.3
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <U8g2lib.h>

#define tx 10 // gps module tx pin to nano d10 pin
#define rx 11

// Create an instance of the U8g2 class for an SSD1306-based OLED display
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

TinyGPSPlus gps;
SoftwareSerial gpsSerial(tx, rx);

const byte ModeButton = 12;
const byte SaveButton = 13;
const byte BatteryPin = A0;
const byte ThermistorPin = A2;

const float R1 = 10000; // Adjust this value for temperature acuracy. 
                  // 10000 is the default. Reducing it makes the temperature go up.
                  // 10000 = 73', 9500 = 76', 9000 = 78'
// Steinhart-Hart Coefficient Values
const float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

byte Mode = 1, o1, o2, o3, a1, a2, a3;
float remainder, HomeLat, HomeLon, HomeAlt;
char CallSign[7];
boolean LastModeButton    = HIGH;
boolean CurrentModeButton = HIGH;

int Vo;      // Thermistor Voltage out
float R2;    // Thermistor
float logR2;
float Tk;    // Temperature in Kelvin
float Tc;    // Temperature in Celsius
float Tf;    // Temperature in Fahrenheit

int offsetHour;  // utc +2 est time
// -7 is USA Pacific Standard Time (PST)

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  pinMode(ModeButton, INPUT_PULLUP); // Uses internal pullup resister
  pinMode(SaveButton, INPUT_PULLUP);

  // Put data in EEPROM (Comment the following 6 lines after the 1st initiation time)
  //EEPROM.put(1, 64.995527);   // Home Latitude 34.198513
  //EEPROM.put(6, 25.500112); // Home Longitude -116.282432
  //EEPROM.put(11, 1);          // Mode
  //EEPROM.put(13, "stella");   // My Callsign
  //EEPROM.put(20, 2750.00);    // Home Altitude 
  //EEPROM.put(25, +2);         // Local time offset Hour

  u8g2.begin(); 
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_fub20_tr);
  u8g2.setCursor(0, 20);
  u8g2.print("Starting...");
  delay(3000);
  u8g2.clearBuffer();
}

void loop() {
  // Get information from the GPS satellites
  unsigned long start = millis();
  do {while (gpsSerial.available()) 
        gps.encode(gpsSerial.read()); 
  } while (millis() - start < 1000); // delay 1s while blocking other tasks

if (digitalRead(ModeButton)==0) // If mode button pressed
  {
    u8g2.clearBuffer();
    Mode = Mode + 1; // Increment the mode
    if (Mode > 9) Mode = 1;  // There are only 9 modes
    EEPROM.put(11, Mode);    // Save the Mode to address 11
    delay(10); // to prevent switch bouncing 
  }

  switch (Mode) // Display GPS information
  {

    case 1:
      // Display Battery Level
      u8x8.setCursor(1,0); // Col, Row
      u8x8.print("Battery Level");
      u8x8.setCursor(3,2); // Col, Row

      float involts = 0.0, readval = 0.0;
      // Read the voltage value at the analog pin
      // 5.0 = the max reference voltage 
      // 1024 = 10 bit analog to digital converter (ADC) (0-1023)
      readval = ((analogRead(BatteryPin) * 5.0) / 1024); 
      // Calculate the input / battery voltage
      // 1026000.00 = two 1 meg ohm resistors
      involts = readval / (1026000.00/(1026000.00+1026000.00)); 
      u8x8.print(involts);
      u8x8.print(" volts");
      u8x8.print("");

      u8x8.setCursor(1,4); // Col, Row
      u8x8.println("Change if under");
      u8x8.setCursor(3,6); // Col, Row
      u8x8.print("6.50 volts");
      break;
      // Display Home Navigation
      u8x8.setCursor(0,0); // Col, Row
      u8x8.print("Home Navigation");
      u8x8.setCursor(2,2); // Col, Row
      u8x8.print(TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), HomeLat, HomeLon)/1000/1.609,2);
      u8x8.print(" miles ");
      u8x8.setCursor(4,4); // Col, Row
      u8x8.print(TinyGPSPlus::courseTo(gps.location.lat(), gps.location.lng(), HomeLat, HomeLon),0);
      u8x8.print("* ");
      u8x8.print(TinyGPSPlus::cardinal(TinyGPSPlus::courseTo(gps.location.lat(), gps.location.lng(), HomeLat, HomeLon)));
      u8x8.print("  ");
      u8x8.setCursor(4,6); // Col, Row
      u8x8.print(gps.course.deg(),0);
      u8x8.print("* ");
      u8x8.print(TinyGPSPlus::cardinal(gps.course.deg()));
      u8x8.print("  ");
      break;
    
 if (gps.location.isUpdated() && gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(" Longitude: ");
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println("Waiting for valid location data...");
  }

  if (gps.time.isUpdated() && gps.time.isValid()) {
    int hour = gps.time.hour();
    int minute = gps.time.minute();
    int second = gps.time.second();

    Serial.print("Time (UTC): ");
    Serial.print(hour < 10 ? "0" : "");
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute < 10 ? "0" : "");
    Serial.print(minute);
    Serial.print(":");
    Serial.print(second < 10 ? "0" : "");
    Serial.println(second);

    u8g2.print("Time (UTC): ");
    u8g2.print(hour < 10 ? "0" : "");
    u8g2.print(hour);
    u8g2.print(":");
    u8g2.print(minute < 10 ? "0" : "");
    u8g2.print(minute);
    u8g2.print(":");
    u8g2.print(second < 10 ? "0" : "");
    u8g2.println(second);
  } else {
    Serial.println("Waiting for valid time data...");
    u8g2.println("Waiting for valid time data...");
  }
  }
  delay(1000);
}


