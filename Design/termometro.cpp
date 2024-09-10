#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Cria o objeto do LCD com o endereço 0x27 e um display de 16 colunas e 2 linhas
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte name0x1[] = { B10000, B01000, B01000, B11100, B01000, B11100, B01000, B11100 };
byte name0x0[] = { B00001, B00010, B00010, B00010, B00010, B00010, B00010, B00010 };
byte name1x0[] = { B00010, B00100, B01000, B01111, B01111, B01111, B00111, B00011 };
byte name1x1[] = { B01000, B00100, B00010, B11110, B11110, B11110, B11100, B11000 };

void setup() {
  // Inicializa o LCD
  lcd.init();
  lcd.backlight();

  lcd.createChar(0, name1x0);
  lcd.setCursor(0, 1);
  lcd.write(0);
  
  lcd.setCursor(2,0);
  lcd.write(223);
  lcd.print("C");

  lcd.setCursor(2,1);
  lcd.print("94");

  lcd.createChar(1, name0x0);
  lcd.setCursor(0,0);
  lcd.write(1);
  
  lcd.createChar(2, name0x1);
  lcd.setCursor(1, 0);
  lcd.write(2);
  
  lcd.createChar(3, name1x1);
  lcd.setCursor(1, 1);
  lcd.write(3);

  // Limpa o display
  // lcd.clear();
}

void loop() {
  // // Move o cursor para a posição (0,0)
  // lcd.setCursor(0, 1);
  // // Imprime o caractere personalizado
  // lcd.write(byte(0));

  // // Aguarda por 5 segundos
  // delay(5000);
}
