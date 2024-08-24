const int vrxPin = A0;  // Analog pin for the X-axis
const int vryPin = A1;  // Analog pin for the Y-axis
const int ledXPin = 3;  // Digital pin for the X-axis LED
const int ledYPin = 4;  // Digital pin for the Y-axis LED

void setup() {
  pinMode(ledXPin, OUTPUT);
  pinMode(ledYPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(vrxPin);  // Read the X-axis value
  int yValue = analogRead(vryPin);  // Read the Y-axis value

  // Map the analog values (0-1023) to PWM values (0-255)
  int ledXValue = map(xValue, 0, 1023, 0, 255);
  int ledYValue = map(yValue, 0, 1023, 0, 255);

  // Set the brightness of the LEDs based on joystick position
  analogWrite(ledXPin, ledXValue);
  analogWrite(ledYPin, ledYValue);

  // Print values to the Serial Monitor for debugging
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | LED X Brightness: ");
  Serial.print(ledXValue);
  Serial.print(" | LED Y Brightness: ");
  Serial.println(ledYValue);

  delay(2000);  // Wait for 100 milliseconds
}