
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_PIN 2
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

byte knownUID[] = {0xAB};  // Your actual RFID tag's UID

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(LED_PIN, OUTPUT);  // Set LED pin as an output
  digitalWrite(LED_PIN, LOW); 

  Serial.println("Scan an RFID card...");
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Show UID on serial monitor
  Serial.print("UID tag: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Compare the read UID with the known UID
  if (compareUID(knownUID, mfrc522.uid.uidByte, mfrc522.uid.size)) {
    Serial.println("Known UID detected!");
    digitalWrite(LED_PIN, HIGH);
    delay(5000);  // Keep the LED on for 5 seconds
    digitalWrite(LED_PIN, LOW);  
  } else {
    Serial.println("Unknown UID.");
    flashLED(LED_PIN, 200);
  }

  delay(1000);
}

bool compareUID(byte *knownUID, byte *readUID, byte length) {
  for (byte i = 0; i < length; i++) {
    if (knownUID[i] != readUID[i]) {
      return false;
    }
  }
  return true;
}

void flashLED(int pin, int duration) {
  unsigned long startMillis = millis();
  while (millis() - startMillis < duration) {
    digitalWrite(pin, HIGH);
    delay(100);  // LED on for 100 milliseconds
    digitalWrite(pin, LOW);
    delay(100);  // LED off for 100 milliseconds
  }
}
