#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte celsius[8] = {
    B00000,
    B01111,
    B01001,
    B01111,
    B00000,
    B00000,
    B00000,
    B00000,
};

#define DHTPIN 2     
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  Serial.println(F("DHT22 example!"));
  lcd.createChar(0, celsius);
  dht.begin();
}

int Celsius[2] = {0, 22};

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C "));
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Temp: "+ String(temperature) + " C");
  lcd.setCursor(0,1);
  lcd.print("Humi: "+ String(humidity) + " %");
  lcd.setCursor(12, 0);
  lcd.write(223);
  // lcd.setCursor(Celsius[0], Celsius[1]);
  // lcd.write(byte(0));

  // Wait a few seconds between measurements.
  delay(2000);
}
