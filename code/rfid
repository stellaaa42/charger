#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

byte knownUID[] = {0xDE, 0xAD, 0xBE, 0xEF};  // CHANGE

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Scan an RFID card...");
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID tag: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  if (compareUID(knownUID, mfrc522.uid.uidByte, mfrc522.uid.size)) {
    Serial.println("Known UID detected!");
    // Add your action here (e.g., unlock a door)
  } else {
    Serial.println("Unknown UID.");
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
