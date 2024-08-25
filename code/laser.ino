const int laserPin = 9; // Digital pin connected to the laser module's Signal (S) pin

void setup() {
  pinMode(laserPin, OUTPUT); // Set the laserPin as an output
  digitalWrite(laserPin, LOW); // Ensure the laser is off initially
}

void loop() {
  digitalWrite(laserPin, HIGH); // Turn on the laser
  delay(1000);                  // Wait for 1 second
  digitalWrite(laserPin, LOW);  // Turn off the laser
  delay(1000);                  // Wait for 1 second
}
