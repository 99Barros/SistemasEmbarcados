#ifndef gota_H
#define gota_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <math.h>

// Declaração das funções e das variáveis externas
extern DHT dht;
extern LiquidCrystal_I2C lcd;

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

void verifyHumidity(int humidity) {
  // Checa se houve erro na leitura
  if (isnan(humidity)) {
    Serial.println(F("Falha no sensor de Luminosidade!"));
    return;
  }
  // Decide qual termômetro mostrar com base na luminosidade
  if (humidity <= 29) {
    // Código para exibir luminosidade entre 1 e 10
    lcd.clear();

    lcd.createChar(2, gotaVazia);

    lcd.setCursor(13, 0);
    lcd.write(2);

    lcd.setCursor(14,1);
    lcd.print("%");
    lcd.setCursor(12,1);
    lcd.print(int(humidity));


  } else if (humidity >= 30 && humidity <= 50) {

    lcd.createChar(2, gotaMedia);

    lcd.setCursor(13, 0);
    lcd.write(2);

    lcd.setCursor(14,1);
    lcd.print("%");
    lcd.setCursor(12,1);
    lcd.print(int(humidity));

  } else if (humidity >= 51 && humidity < 100) {

    lcd.createChar(2, gotaCheia);

    lcd.setCursor(13, 0);
    lcd.write(2);

    lcd.setCursor(14,1);
    lcd.print("%");
    lcd.setCursor(12,1);
    lcd.print(int(humidity));

  }else if (humidity = 100 ) {

    lcd.createChar(2, gotaCheia);

    lcd.setCursor(13, 0);
    lcd.write(2);

    lcd.setCursor(15,1);
    lcd.print("%");
    lcd.setCursor(12,1);
    lcd.print(int(humidity));

  }
}

#endif