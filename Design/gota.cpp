#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

byte name0x11[] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte name0x5[] = { B00001, B00001, B00001, B00010, B00010, B00100, B00100, B01000 };
byte name0x6[] = { B00000, B00000, B00000, B10000, B10000, B01000, B01000, B00100 };
byte name1x5[] = { B01000, B10000, B10000, B10000, B01000, B01000, B00100, B00011 };
byte name1x6[] = { B00100, B00010, B00010, B00010, B00100, B00100, B01000, B10000 };

byte name1x6_1[] = { B00100, B00010, B00010, B00010, B00100, B11100, B11000, B10000 };
byte name0x5_1[] = { B00001, B00001, B00001, B00010, B00010, B00100, B00100, B01000 };
byte name0x6_1[] = { B00000, B00000, B00000, B10000, B10000, B01000, B01000, B00100 };
byte name1x5_1[] = { B01000, B10000, B10000, B10000, B01000, B01111, B00111, B00011 };

byte name1x6_2[] = { B00100, B00010, B00010, B11110, B11100, B11100, B11000, B10000 };
byte name0x5_2[] = { B00001, B00001, B00001, B00010, B00010, B00100, B00100, B01000 };
byte name0x6_2[] = { B00000, B00000, B00000, B10000, B10000, B01000, B01000, B00100 };
byte name1x5_2[] = { B01000, B10000, B10000, B11111, B01111, B01111, B00111, B00011 };

byte name1x5_3[] = { B01000, B11111, B11111, B11111, B01111, B01111, B00111, B00011 };
byte name0x5_3[] = { B00001, B00001, B00001, B00010, B00010, B00100, B00100, B01000 };
byte name0x6_3[] = { B00000, B00000, B00000, B10000, B10000, B01000, B01000, B00100 };
byte name1x6_3[] = { B00100, B11110, B11110, B11110, B11100, B11100, B11000, B10000 };

byte name0x6_4[] = { B00000, B00000, B00000, B10000, B10000, B01000, B01000, B11100 };
byte name0x5_4[] = { B00001, B00001, B00001, B00010, B00010, B00100, B00100, B01111 };
byte name1x5_4[] = { B01111, B11111, B11111, B11111, B01111, B01111, B00111, B00011 };
byte name1x6_4[] = { B11100, B11110, B11110, B11110, B11100, B11100, B11000, B10000 };

byte name0x5_5[] = { B00001, B00001, B00001, B00011, B00011, B00111, B00111, B01111 };
byte name0x6_5[] = { B00000, B00000, B00000, B10000, B10000, B11000, B11000, B11100 };
byte name1x5_5[] = { B01111, B11111, B11111, B11111, B01111, B01111, B00111, B00011 };
byte name1x6_5[] = { B11100, B11110, B11110, B11110, B11100, B11100, B11000, B10000 };

//Gota Certa
byte gotaVazia[] = {
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110
};

byte gotaMedia[] = {
  B00100, 
  B00100,
  B01010,
  B01010,
  B10001,
  B11111,
  B11111,
  B01110
};

byte gotaCheia[] = {
  B00100,
  B00100,
  B01110,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110
};

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
