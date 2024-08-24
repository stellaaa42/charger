#include <OneWire.h>
#include <DallasTemperature.h>

// Pin where the DS18820 data line is connected
const int oneWireBus = 2;

// Setup a OneWire instance
OneWire oneWire(oneWireBus);

// Pass the OneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();  // Initialize the sensors
}

void loop() {
  sensors.requestTemperatures();  // Request temperature readings
  float temperatureC = sensors.getTempCByIndex(0);  // Read temperature in Celsius

  if (temperatureC != DEVICE_DISCONNECTED_C) {
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" °C");
  } else {
    Serial.println("Error: Could not read temperature data");
  }

  delay(1000);  // Wait for 1 second before the next reading
}