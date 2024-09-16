#ifndef termometro_H
#define termometro_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <math.h>

// Declaração das funções e das variáveis externas
extern DHT dht;
extern LiquidCrystal_I2C lcd;

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

void verificaTemperatura(int temperature) {
  // Checa se houve erro na leitura
  if (isnan(temperature)) {
    Serial.println(F("Falha no sensor de Temperatura!"));
    return;
  }
  // Decide qual termômetro mostrar com base na temperatura
  if (temperature >= 0 && temperature <= 14) {
    lcd.createChar(0, termometroVazio);
    lcd.setCursor(2, 0);
    lcd.write(0);
    lcd.setCursor(3,1);
    lcd.write(223);
    lcd.print("C");
    lcd.setCursor(1,1);
    lcd.print(int(temperature));

  } else if (temperature >= 15 && temperature <= 25) {
    lcd.createChar(0, termometroMedio);
    lcd.setCursor(2, 0);
    lcd.write(0);
    lcd.setCursor(3,1);
    lcd.write(223);
    lcd.print("C");
    lcd.setCursor(1,1);
    lcd.print(int(temperature));

  } else if (temperature > 26) {

    lcd.createChar(0, termometroCheio);
    lcd.setCursor(2, 0);
    lcd.write(0);
    lcd.setCursor(3,1);
    lcd.write(223);
    lcd.print("C");
    lcd.setCursor(1,1);
    lcd.print(int(temperature));
  }else if (temperature < 0) {

    lcd.createChar(0, termometroVazio);
    lcd.setCursor(2, 0);
    lcd.write(0);
    lcd.setCursor(3,1);
    lcd.write(223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print(int(temperature));
  }
}

#endif