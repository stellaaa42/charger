const int trigPin = 9;  // Pin connected to the Trigger pin of the HC-SR04
const int echoPin = 10; // Pin connected to the Echo pin of the HC-SR04

void setup() {
  pinMode(trigPin, OUTPUT); // Set the trigger pin as an output
  pinMode(echoPin, INPUT);  // Set the echo pin as an input
  Serial.begin(9600);       // Start serial communication
}

void loop() {
  long duration, distance;

  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond pulse to trigger
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = (duration / 2) / 29.1;

  // Print the distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Delay between measurements
  delay(500);
}
