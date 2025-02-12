#include <SPI.h>
#include <MFRC522.h>
#include <TFT_eSPI.h> // Hardware-specific library

#define RST_PIN 17 // Configurable, see typical pin layout above
#define SS_PIN 33 // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

void setup() {
Serial.begin(9600); // Initialize serial communications with the PC
while (!Serial); // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

pinMode(RST_PIN, OUTPUT);
digitalWrite(RST_PIN, HIGH);
Serial.println("HELLO");
Serial.println(digitalRead(RST_PIN));
tft.init();

tft.fillScreen(TFT_WHITE);

SPI.begin(25,27,26);            // Init SPI bus CLK, MISO, MOSI
mfrc522.PCD_Init();     // Init MFRC522
delay(4);               // Optional delay. Some board do need more time after init to be ready, see Readme
mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
if ( ! mfrc522.PICC_IsNewCardPresent()) {
return;
}

// Select one of the cards
if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
}

// Dump debug info about the card; PICC_HaltA() is automatically called
mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}