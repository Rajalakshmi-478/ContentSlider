#include <Arduino.h>
#include <Encoder.h>
#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>

#define LED_PIN1 9
#define LED_PIN2 8
#define ENCODER_A_PIN 2
#define ENCODER_B_PIN 3
#define SS_PIN 10
#define RST_PIN 5

Encoder encoder(ENCODER_A_PIN, ENCODER_B_PIN);
MFRC522 rfid(SS_PIN, RST_PIN);

long position = 0;
long A = 0;
String uidString;
String number;
String preUid;
const long minEncoderValue = 0;
const long maxEncoderValue = 200;

const int maxNumberCount = 10;
String numberArray[maxNumberCount];
int numberCount = 0;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
}

void loop() {
  DynamicJsonDocument jsonDoc(128);
  
  long newPosition = encoder.read();
  if (newPosition < minEncoderValue) {
    newPosition = minEncoderValue;
  } else if (newPosition > maxEncoderValue) {
    newPosition = maxEncoderValue;
  }
  long positionChange = newPosition - position;
  if (positionChange > 0 || position >= -positionChange) {
    position = newPosition;
  }
  A = position;

  jsonDoc["A"] = A;
  if (A == maxEncoderValue) {
    digitalWrite(LED_PIN1, HIGH);
  } else if (A == minEncoderValue) {
    digitalWrite(LED_PIN2, HIGH);
  } else {
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, LOW);
  }

  // Your existing code...

  if (rfid.PICC_IsNewCardPresent()) {
    if (rfid.PICC_ReadCardSerial()) {
      String uidString = "";
      for (int i = 0; i < rfid.uid.size; i++) {
        char buffer[3];
        sprintf(buffer, "%02X", rfid.uid.uidByte[i]);
        uidString += buffer;
      }

      number = uidString;
      preUid = uidString;

      // Reset encoder data when a new card is detected
      resetEncoderData();

      // Store number in the array if it's not already in the array
      if (!isNumberInArray(number)) {
        if (numberCount < maxNumberCount) {
          numberArray[numberCount] = number;
          numberCount++;
        }
      }

      jsonDoc["UID"] = uidString;
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
    } else {
      jsonDoc["UID"] = uidString;
    }
  }

  jsonDoc["UID"] = number;
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  Serial.println(jsonString);
}

bool isNumberInArray(const String &num) {
  for (int i = 0; i < numberCount; i++) {
    if (numberArray[i] == num) {
      return true;
    }
  }
  return false;
}

void resetEncoderData() {
  encoder.write(0);  // Reset encoder position to 0
  position = 0;
}
