// transistor motor
const int motorPin = 9;


void setup() {
  pinMode(motorPin, OUTPUT);
}


void loop() {
  analogWrite(motorPin, 0); // Activate relay (turn on green LED) // Turn on motor at full speed
  delay(4000);                  // Run for 1 second

  analogWrite(motorPin, 255);  // Deactivate relay (turn on red LED)    // Turn off motor
  delay(4000);                  // Wait for 1 second

}
