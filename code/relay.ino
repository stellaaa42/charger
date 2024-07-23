
int relayPin = 2;  // Pin connected to IN of relay

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Initialize relay to be off
}

void loop() {
  digitalWrite(relayPin, HIGH);  // Turn relay on
  Serial.println("Pin D2 is HIGH");
  delay(5000);  // Wait for 100 second
  digitalWrite(relayPin, LOW);   // Turn relay off
  Serial.println("Pin D2 is LOW");
  delay(5000);  // Wait for a second
}
