#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

byte name0x11[] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte name0x5[] = { B00001, B00001, B00001, B00010, B00010, B00100, B00100, B01000 };
byte name0x6[] = { B00000, B00000, B00000, B10000, B10000, B01000, B01000, B00100 };
byte name1x5[] = { B01000, B10000, B10000, B10000, B01000, B01000, B00100, B00011 };
byte name1x6[] = { B00100, B00010, B00010, B00010, B00100, B00100, B01000, B10000 };

void setup() {
  lcd.begin(16, 2);
  
  lcd.createChar(0, name0x11);
  lcd.setCursor(11, 0);
  lcd.write(0);
  
  lcd.createChar(1, name0x5);
  lcd.setCursor(5, 0);
  lcd.write(1);
  
  lcd.createChar(2, name0x6);
  lcd.setCursor(6, 0);
  lcd.write(2);
  
  lcd.createChar(3, name1x5);
  lcd.setCursor(5, 1);
  lcd.write(3);
  
  lcd.createChar(4, name1x6);
  lcd.setCursor(6, 1);
  lcd.write(4);
}

void loop() {};
