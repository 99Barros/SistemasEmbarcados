#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <math.h>

#define DHTPIN 2     
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

// Cria o objeto do LCD com o endereço 0x27 e um display de 16 colunas e 2 linhas
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte name0x0[] = { B00001, B00010, B00010, B00010, B00010, B00010, B00010, B00010 };
byte name0x1[] = { B10000, B01100, B01000, B01100, B01000, B01100, B01000, B01100 };
byte name1x0[] = { B00010, B00100, B01000, B01000, B01000, B01000, B00100, B00011 };
byte name1x1[] = { B01000, B00100, B00010, B00010, B00010, B00010, B00100, B11000 };

byte name0x0_1[] = { B00001, B00010, B00010, B00010, B00010, B00010, B00010, B00010 };
byte name0x1_1[] = { B10000, B01100, B01000, B01100, B01000, B01100, B01000, B01100 };
byte name1x0_1[] = { B00010, B00100, B01000, B01000, B01111, B01111, B00111, B00011 };
byte name1x1_1[] = { B01000, B00100, B00010, B00010, B11110, B11110, B11100, B11000 };

byte name0x0_2[] = { B00001, B00010, B00010, B00010, B00010, B00010, B00010, B00010 };
byte name0x1_2[] = { B10000, B01100, B01000, B01100, B01000, B01100, B01000, B01100 };
byte name1x0_2[] = { B00010, B00111, B01111, B01111, B01111, B01111, B00111, B00011 };
byte name1x1_2[] = { B01000, B11100, B11110, B11110, B11110, B11110, B11100, B11000 };

byte name0x0_3[] = { B00001, B00010, B00010, B00010, B00010, B00010, B00010, B00011 };
byte name0x1_3[] = { B10000, B01100, B01000, B01100, B01000, B01100, B01000, B11100 };
byte name1x0_3[] = { B00011, B00111, B01111, B01111, B01111, B01111, B00111, B00011 };
byte name1x1_3[] = { B11000, B11100, B11110, B11110, B11110, B11110, B11100, B11000 };

byte name0x0_4[] = { B00001, B00010, B00010, B00010, B00010, B00011, B00011, B00011 };
byte name0x1_4[] = { B10000, B01100, B01000, B01100, B01000, B11100, B11000, B11100 };
byte name1x0_4[] = { B00011, B00111, B01111, B01111, B01111, B01111, B00111, B00011 };
byte name1x1_4[] = { B11000, B11100, B11110, B11110, B11110, B11110, B11100, B11000 };

byte name0x0_5[] = { B00001, B00010, B00010, B00011, B00011, B00011, B00011, B00011 };
byte name0x1_5[] = { B10000, B01100, B01000, B11100, B11000, B11100, B11000, B11100 };
byte name1x0_5[] = { B00011, B00111, B01111, B01111, B01111, B01111, B00111, B00011 };
byte name1x1_5[] = { B11000, B11100, B11110, B11110, B11110, B11110, B11100, B11000 };

byte name0x0_6[] = { B00001, B00011, B00011, B00011, B00011, B00011, B00011, B00011 };
byte name0x1_6[] = { B10000, B11100, B11000, B11100, B11000, B11100, B11000, B11100 };
byte name1x0_6[] = { B00011, B00111, B01111, B01111, B01111, B01111, B00111, B00011 };
byte name1x1_6[] = { B11000, B11100, B11110, B11110, B11110, B11110, B11100, B11000 };

//Termometro Certo
byte termometroVazio[] = {
  B01110,
  B01010,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110
};

byte termometroMedio[] = {
  B01110,
  B01010,
  B01010,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110
};

byte termometroCheio[] = {
  B01110,
  B01110,
  B01110,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110
};

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT22 example!"));

  dht.begin();
  // Inicializa o LCD
  lcd.init();
  lcd.backlight();

  // Limpa o display
  // lcd.clear();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  if(temperature <= 0 ){
    lcd.createChar(0, name1x0);
    lcd.setCursor(0, 1);
    lcd.write(0);
    
    lcd.setCursor(2,0);
    lcd.write(223);
    lcd.print("C");

    lcd.setCursor(2,1);
    lcd.print(int(temperature));

    lcd.createChar(1, name0x0);
    lcd.setCursor(0,0);
    lcd.write(1);
    
    lcd.createChar(2, name0x1);
    lcd.setCursor(1, 0);
    lcd.write(2);
    
    lcd.createChar(3, name1x1);
    lcd.setCursor(1, 1);
    lcd.write(3);
  }

  if(temperature >= 1 && temperature <= 10)
  {
    lcd.createChar(0, name1x0_1);
    lcd.setCursor(0, 1);
    lcd.write(0);
    
    lcd.setCursor(2,0);
    lcd.write(223);
    lcd.print("C");

    lcd.setCursor(2,1);
    lcd.print(int(temperature));

    lcd.createChar(1, name0x0_1);
    lcd.setCursor(0,0);
    lcd.write(1);
    
    lcd.createChar(2, name0x1_1);
    lcd.setCursor(1, 0);
    lcd.write(2);
    
    lcd.createChar(3, name1x1_1);
    lcd.setCursor(1, 1);
    lcd.write(3);
  }

  if(temperature >= 11 && temperature <= 20)
  {
    lcd.createChar(0, name1x0_2);
    lcd.setCursor(0, 1);
    lcd.write(0);
    
    lcd.setCursor(2,0);
    lcd.write(223);
    lcd.print("C");

    lcd.setCursor(2,1);
    lcd.print(int(temperature));

    lcd.createChar(1, name0x0_2);
    lcd.setCursor(0,0);
    lcd.write(1);
    
    lcd.createChar(2, name0x1_2);
    lcd.setCursor(1, 0);
    lcd.write(2);
    
    lcd.createChar(3, name1x1_2);
    lcd.setCursor(1, 1);
    lcd.write(3);
  }

  if(temperature >= 21 && temperature <= 30)
  {
    lcd.createChar(0, name1x0_3);
    lcd.setCursor(0, 1);
    lcd.write(0);
    
    lcd.setCursor(2,0);
    lcd.write(223);
    lcd.print("C");

    lcd.setCursor(2,1);
    lcd.print(int(temperature));

    lcd.createChar(1, name0x0_3);
    lcd.setCursor(0,0);
    lcd.write(1);
    
    lcd.createChar(2, name0x1_3);
    lcd.setCursor(1, 0);
    lcd.write(2);
    
    lcd.createChar(3, name1x1_3);
    lcd.setCursor(1, 1);
    lcd.write(3);
  }

  
  if(temperature >= 31 && temperature <= 40)
  {
    lcd.createChar(0, name1x0_4);
    lcd.setCursor(0, 1);
    lcd.write(0);
    
    lcd.setCursor(2,0);
    lcd.write(223);
    lcd.print("C");

    lcd.setCursor(2,1);
    lcd.print(int(temperature));

    lcd.createChar(1, name0x0_4);
    lcd.setCursor(0,0);
    lcd.write(1);
    
    lcd.createChar(2, name0x1_4);
    lcd.setCursor(1, 0);
    lcd.write(2);
    
    lcd.createChar(3, name1x1_4);
    lcd.setCursor(1, 1);
    lcd.write(3);
  }

    if(temperature >= 41 && temperature <= 50)
  {
    lcd.createChar(0, name1x0_5);
    lcd.setCursor(0, 1);
    lcd.write(0);
    
    lcd.setCursor(2,0);
    lcd.write(223);
    lcd.print("C");

    lcd.setCursor(2,1);
    lcd.print(int(temperature));

    lcd.createChar(1, name0x0_5);
    lcd.setCursor(0,0);
    lcd.write(1);
    
    lcd.createChar(2, name0x1_5);
    lcd.setCursor(1, 0);
    lcd.write(2);
    
    lcd.createChar(3, name1x1_5);
    lcd.setCursor(1, 1);
    lcd.write(3);
  }

    if(temperature >= 51)
  {
    lcd.createChar(0, name1x0_6);
    lcd.setCursor(0, 1);
    lcd.write(0);
    
    lcd.setCursor(2,0);
    lcd.write(223);
    lcd.print("C");

    lcd.setCursor(2,1);
    lcd.print(int(temperature));

    lcd.createChar(1, name0x0_6);
    lcd.setCursor(0,0);
    lcd.write(1);
    
    lcd.createChar(2, name0x1_6);
    lcd.setCursor(1, 0);
    lcd.write(2);
    
    lcd.createChar(3, name1x1_6);
    lcd.setCursor(1, 1);
    lcd.write(3);
  }

  // // Move o cursor para a posição (0,0)
  // lcd.setCursor(0, 1);
  // // Imprime o caractere personalizado
  // lcd.write(byte(0));

  // // Aguarda por 5 segundos
  // delay(5000);
}
