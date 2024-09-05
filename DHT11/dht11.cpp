#include "DHT.h"
#include <LiquidCrystal_I2C.h>
// #include <RTClib.h>
// #include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
// RTC_DS3231 rtc;

#define DHTPIN 2     
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  Serial.println(F("DHT22 example!"));

  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  // float trigger_t_max = 60.0;
  // float trigger_t_min = 30.0;
  // float trigger_u_max = 30.0;
  // float trigger_u_min = 10.0;
  // DateTime now = rtc.now();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature) || isnan(humidity)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Serial.print(F("Humidity: "));
  // Serial.print(humidity);
  // Serial.print(F("%  Temperature: "));
  // Serial.print(temperature);
  // Serial.println(F("°C "));

  lcd.setCursor(0,0);
  lcd.print("Temp: "+ String(temperature));
  lcd.setCursor(11,0);
  lcd.write(223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humi: "+ String(humidity));
  lcd.setCursor(12,1);
  lcd.print("%");

  // if(temperature < trigger_t_max)
  // {
  //   Serial.print(now.day(), DEC);        // Dia
  //   Serial.print("/");
  //   Serial.print(now.month(), DEC);      // Mês
  //   Serial.print("/");
  //   Serial.print(now.year(), DEC);       // Ano
  //   Serial.print(" ");
  //   Serial.print(now.hour(), DEC);       // Hora
  //   Serial.print(":");
  //   Serial.print(now.minute(), DEC);     // Minuto
  //   Serial.print(":");
  //   Serial.print(now.second(), DEC);     // Segundo
  // }

  // Wait a few seconds between measurements.
  delay(2000);
}
