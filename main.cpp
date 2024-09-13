#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <EEPROM.h>
#include <RTClib.h> // Biblioteca para Relógio em Tempo Real
#include <Wire.h>   // Biblioteca para comunicação I2C


int ValorLDR;       // Armazenar a leitura do sensor LDR
int IntensidadeLuz; // Transforma a leitura em uma escala de 0 a 100
int pinoLDR = A0;   // PINO ANALÓGICO utilizado para ler o LDR

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 2     
#define DHTTYPE DHT22
#define UTC_OFFSET -3
#define SERIAL_OPTION 0    
int lastLoggedMinute = -1;

RTC_DS1307 RTC;
DHT dht(DHTPIN, DHTTYPE);

// SETUP EEPROM
const int maxRecords = 100;
const int recordSize = 12; // Tamanho de cada registro em bytes
int startAddress = 0;
int endAddress = maxRecords * recordSize;
int currentAddress = 0;
void getNextAddress() {
    currentAddress += recordSize;
    if (currentAddress >= endAddress) {
        currentAddress = 0; // Volta para o começo se atingir o limite
    }
}

void get_log() {
    Serial.println("Data stored in EEPROM:");
    Serial.println("Timestamp\t\tTemperature\tHumidity\tLuminosity");

    for (int address = startAddress; address < endAddress; address += recordSize) {
        long timeStamp;
        int tempInt, humiInt, luminosityInt;

        // Ler dados da EEPROM
        EEPROM.get(address, timeStamp);
        EEPROM.get(address + 4, tempInt);
        EEPROM.get(address + 6, humiInt);
        EEPROM.get(address + 8, luminosityInt);

        // Verificar se os dados são válidos antes de imprimir
        if (timeStamp > 0 && timeStamp < 0xFFFFFFFF) { // Checando se o timestamp é válido
            DateTime dt = DateTime(timeStamp);
            Serial.print(dt.timestamp(DateTime::TIMESTAMP_FULL));
            Serial.print("\t");
            Serial.print(tempInt / 100.0); // Convertendo o valor de volta para o formato float
            Serial.print(" C\t\t");
            Serial.print(humiInt / 100.0); // Convertendo o valor de volta para o formato float
            Serial.print(" %\t\t");
            Serial.print(luminosityInt); // Luminosidade como está
            Serial.println(" %");
        }
    }
}


void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
    dht.begin();
    RTC.begin();    // Inicialização do Relógio em Tempo Real
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // RTC.adjust(DateTime(2024, 5, 6, 08, 15, 00));

    Serial.begin(9600);      // Define a velocidade do monitor serial
    pinMode(pinoLDR, INPUT); // Define o pino que o LDR está ligado como entrada de dados
    EEPROM.begin();
}
int ControleLuminosidade(int ValorLDR)
{
    IntensidadeLuz = map(ValorLDR, 958, 205, 0, 100);
    if (IntensidadeLuz < 0)
    {
        IntensidadeLuz = 0;
    }
    else if (IntensidadeLuz > 100)
    {
        IntensidadeLuz = 100;
    }
    return IntensidadeLuz;
}
  bool MedeLimite(int grandeza,int minimo, int maximo)
    {
      if (grandeza < minimo || grandeza > maximo){
        return false;
      }
      else return true;

    }
void loop()
{
    DateTime now = RTC.now();

    // Calculando o deslocamento do fuso horário
    int offsetSeconds = UTC_OFFSET * 3600; // Convertendo horas para segundos
    now = now.unixtime() + offsetSeconds; 
    DateTime adjustedTime = DateTime(now);// Adicionando o deslocamento ao tempo atual
    get_log();
    // Convertendo o novo tempo para DateTime
    
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    ValorLDR = analogRead(pinoLDR);  
    int luminosidade = ControleLuminosidade(ValorLDR);
  // Verifica se o minuto atual é diferente do minuto do último registro
    if (adjustedTime.minute() != lastLoggedMinute) {
    lastLoggedMinute = adjustedTime.minute(); 
    lcd.clear();
    lcd.print("Checando se as grandezas estão no padrão...")  ;
    lcd.clear();
    bool teste_luminosidade = MedeLimite(luminosidade, 0, 30 );
    bool teste_temperature = MedeLimite(temperature, 15, 25 );
    bool teste_humidity = MedeLimite(humidity, 30, 50 );
    delay(100)   ;
    int delayTotal = 10000;
    lcd.setCursor(0, 0);
    lcd.setCursor(0, 0);  // Posiciona o cursor corretamente
    lcd.print("I:");    
    lcd.print(luminosidade);
    lcd.setCursor(3, 1);
    lcd.print("T:");
    lcd.print(temperature);
    lcd.setCursor(12, 0); 
    lcd.print("U:");
    lcd.print(humidity);
    delay(delayTotal);    
   
 if (!teste_luminosidade) {
    for (int i = 0; i < delayTotal / 10; i++) {
        lcd.setCursor(0, 0);
        
        // Pisca: exibe o valor de luminosidade por metade do tempo
        if (i % 2 == 0) {
            lcd.print("I:");    
            lcd.print(luminosidade);
        } else {
            // Limpa o campo para simular o "piscar"
            lcd.print("    ");  // Espaços para apagar o valor
        }

        delay(delayTotal / 10);  // Aguarda para a próxima piscada
    }
}
//

//a

    if(!(teste_luminosidade || teste_temperature || teste_humidity)){

    int tempInt = (int)(temperature * 100);
    int humiInt = (int)(humidity * 100);
   //
    EEPROM.put(currentAddress, now.unixtime());
    EEPROM.put(currentAddress + 4, tempInt);
    EEPROM.put(currentAddress + 6, humiInt);
    EEPROM.put(currentAddress + 8, luminosidade);
    Serial.println("Grandezas foras dos padrões");

    getNextAddress(); 
    }    
        
  if (isnan(temperature) || isnan(humidity)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  } 

    }
    lcd.setCursor(0, 0);
    lcd.print("DATA: ");
    lcd.print(adjustedTime.day() < 10 ? "0" : ""); // Adiciona zero à esquerda se dia for menor que 10
    lcd.print(adjustedTime.day());
    lcd.print("/");
    lcd.print(adjustedTime.month() < 10 ? "0" : ""); // Adiciona zero à esquerda se mês for menor que 10
    lcd.print(adjustedTime.month());
    lcd.print("/");
    lcd.print(adjustedTime.year());
    lcd.setCursor(0, 1);
    lcd.print("HORA: ");
    lcd.print(adjustedTime.hour() < 10 ? "0" : ""); // Adiciona zero à esquerda se hora for menor que 10
    lcd.print(adjustedTime.hour());
    lcd.print(":");
    lcd.print(adjustedTime.minute() < 10 ? "0" : ""); // Adiciona zero à esquerda se minuto for menor que 10
    lcd.print(adjustedTime.minute());
    lcd.print(":");
    lcd.print(adjustedTime.second() < 10 ? "0" : ""); // Adiciona zero à esquerda se segundo for menor que 10
    lcd.print(adjustedTime.second());

    delay(1000);
    lcd.clear();
            

}
   

    