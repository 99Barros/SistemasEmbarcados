#ifndef raio_H
#define raio_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <math.h>

// Declaração das funções e das variáveis externas
extern DHT dht;
extern LiquidCrystal_I2C lcd;

byte raioVazio[] = {
  B00000,
  B00010,
  B00100,
  B01110,
  B00100,
  B01000,
  B00000,
  B00000
};

byte raioMedio[] = {
  B00011,
  B00110,
  B01100,
  B11111,
  B00110,
  B01100,
  B11000,
  B00000
};

byte raioCheio[] = {
  B00011,
  B00110,
  B01100,
  B11111,
  B11111,
  B00110,
  B01100,
  B11000
};

void verifyLuminosity(int luminosity) {
  // Checa se houve erro na leitura
  if (isnan(luminosity)) {
    Serial.println(F("Falha no sensor de Luminosidade!"));
    return;
  }
  // Decide qual termômetro mostrar com base na luminosidade
  if (luminosity <= 30) {
    lcd.createChar(1, raioVazio);

    lcd.setCursor(8, 0);
    lcd.write(1);

    lcd.setCursor(9,1);
    lcd.print("%");

    lcd.setCursor(7,1);
    lcd.print(int(luminosity));

  } else if (luminosity >= 31 && luminosity <= 70) {
    lcd.createChar(1, raioMedio);

    lcd.setCursor(8, 0);
    lcd.write(1);

    lcd.setCursor(9,1);
    lcd.print("%");

    lcd.setCursor(7,1);
    lcd.print(int(luminosity));


  } else if (luminosity >= 71 && luminosity < 100) {
    lcd.createChar(1, raioCheio);

    lcd.setCursor(8, 0);
    lcd.write(1);

    lcd.setCursor(9,1);
    lcd.print("%");

    lcd.setCursor(7,1);
    lcd.print(int(luminosity));

  } else if (luminosity = 100) {
    lcd.createChar(1, raioCheio);

    lcd.setCursor(8, 0);
    lcd.write(1);

    lcd.setCursor(10,1);
    lcd.print("%");

    lcd.setCursor(7,1);
    lcd.print(int(luminosity));
  }
}

#endif