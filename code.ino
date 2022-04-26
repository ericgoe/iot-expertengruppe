#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include "rgb_lcd.h"
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
rgb_lcd lcd;

 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.begin(16, 2);
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Key:");
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  lcd.print(content);
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  lcd.setCursor(0,1);
  

  if (content.substring(1) == "69 63 B0 63" || content.substring(1) == "B5 35 58 D3" || content.substring(1) == "52 13 50 D3") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    lcd.setRGB(0, 255, 0);
    lcd.print("Approved access");
    Serial.println();
    delay(3000);
  }
 
 else   {
    lcd.setRGB(255, 0, 0);
    Serial.println("Access denied");
    lcd.print("Access denied");
    delay(3000);
  }
} 
