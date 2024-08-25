const int pinDT = 2;  // Digital pin connected to the DT pin of the encoder
const int pinCLK = 3; // Digital pin connected to the CLK pin of the encoder
const int debounceDelay = 5; // Debounce delay in milliseconds

volatile int encoderPos = 0; // Variable to store encoder position
int lastEncoded = 0;        // Last encoded value
unsigned long lastInterruptTime = 0; // Last interrupt time for debounce

void setup() {
  pinMode(pinDT, INPUT);
  pinMode(pinCLK, INPUT);

  Serial.begin(9600);

  // Attach interrupts to handle encoder changes
  attachInterrupt(digitalPinToInterrupt(pinDT), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinCLK), updateEncoder, CHANGE);
}

void loop() {
  // Print the encoder position every second
  static unsigned long lastPrintTime = 0;
  if (millis() - lastPrintTime > 1000) {
    lastPrintTime = millis();
    Serial.print("Encoder Position: ");
    Serial.println(encoderPos);
  }
}

void updateEncoder() {
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTime > debounceDelay) {
    int MSB = digitalRead(pinDT); // MSB = most significant bit
    int LSB = digitalRead(pinCLK); // LSB = least significant bit

    int encoded = (MSB << 1) | LSB; // Convert the encoder signals to binary
    int sum = (lastEncoded << 2) | encoded; // Combine previous and current states

    // Determine the direction of rotation
    if (sum == 0b1101 || sum == 0b0110 || sum == 0b1011 || sum == 0b0100) {
      encoderPos++; // Clockwise
    } else if (sum == 0b0101 || sum == 0b1010 || sum == 0b1110 || sum == 0b0001) {
      encoderPos--; // Counterclockwise
    }

    lastEncoded = encoded; // Store the current state for the next update
    lastInterruptTime = currentTime; // Update last interrupt time
  }
}
