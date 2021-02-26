#include <SPI.h>
#include <Servo.h>
#include "pitches.h"
#include <Wire.h>
RFID rfid(35, 37); // Define the RFID
byte card[37] = {0x4D, 0x55, 0xAD, 0xD3, 0x66};
byte serNum[37];
byte data[37];
int servoPin = 10; // Pin connected to servo
Servo doorLock; // Define the servomotor
void setup() {
  doorLock.attach(servoPin); // Set servo as a pin
  Serial.begin(9600); // Start serial communication
  SPI.begin(); // Start serial communication between the RFID and PC
  rfid.init(); // Initialize the RFID
  Serial.println("Arduino card reader");
  delay(1000);
  pinMode(servoPin, OUTPUT);
}
void loop() { // Create a variable for each user
  boolean card_card = true; // Define your card
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      delay(1000);
      data[0] = rfid.serNum[0];
      data[1] = rfid.serNum[1];
      data[2] = rfid.serNum[2];
      data[3] = rfid.serNum[3];
      data[4] = rfid.serNum[4];
    }
    Serial.print("Card found - code:");
    for (int i = 0; i < 5; i++) {
          }

    char tbs[16];
    sprintf(tbs, "%2x %2x %2x %2x %2x", data[0], data[1], data[2], data[3], data[4]);
    Serial.println(tbs);    
    Serial.println();
    if (card_card) { // A card with access permission is found
      Serial.println("Hello Mark!"); // Print to Serial Monitor
    }
    else { // If the card is not recognized
      Serial.println("Card not recognized! Contact administrator!");
      delay(1000);
    }
    if (card_card) { // Add other users with access here
      Serial.println("Access granted.......Welcome!");
      doorLock.write(180); // Turn servo 180 degrees
      delay(5000); // Wait for 5 seconds
      doorLock.write(0); // Turn servo back to 0 degrees
    }
    Serial.println();
    delay(500);
    rfid.halt();
  }
}
