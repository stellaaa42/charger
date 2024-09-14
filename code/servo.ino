#include <Servo.h>  // Include the Servo library

Servo myServo;      // Create a Servo object
int pos;

void setup() {
  myServo.attach(7);  // Attach the servo to pin 9 (PWM pin)
}

void loop() {
  pos = 90;
  myServo.write(pos);
}
