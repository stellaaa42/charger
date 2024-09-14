#include <Servo.h>

#define CLK 2  // Rotary encoder CLK pin
#define DT 3   // Rotary encoder DT pin
#define SW 4   // Rotary encoder switch pin (optional)

Servo myServo;
int currentPos = 90;  // Initial servo position
int lastStateCLK;
int counter = 0;

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);  // Switch pin with pull-up resistor

  myServo.attach(9);
  myServo.write(currentPos);

  lastStateCLK = digitalRead(CLK);  // Initialize last state

  Serial.begin(9600);  // Debugging
}

void loop() {
  // Check for rotation
  int currentStateCLK = digitalRead(CLK);

  if (currentStateCLK != lastStateCLK) {
    // Determine direction by comparing DT and CLK
    counter += (digitalRead(DT) != currentStateCLK) ? 1 : -1;

    // Map the counter value to a range for servo (0-180)
    currentPos = constrain(map(counter, -50, 50, 0, 180), 0, 180);
    myServo.write(currentPos);

    Serial.print("Position: ");
    Serial.println(currentPos);
  }

  lastStateCLK = currentStateCLK;  // Update the last state

  // Optional button press check
  if (digitalRead(SW) == LOW) {
    Serial.println("Button Pressed");
    delay(500);  // Simple debounce
  }
  
  delay(5);  // Reduced delay for faster response
}
