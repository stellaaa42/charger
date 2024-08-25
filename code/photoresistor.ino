int sensorPin = A0;    // Pin connected to the junction point
int sensorValue = 0;   // Variable to store the sensor value

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 bps
}

void loop() {
  sensorValue = analogRead(sensorPin);  // Read the value from the photoresistor
  Serial.print("Light Level: ");
  Serial.println(sensorValue);          // Print the value to the Serial Monitor
  delay(1000);                          // Wait for 1 second before reading again
}
