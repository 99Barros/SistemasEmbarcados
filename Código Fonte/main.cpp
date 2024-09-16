#include <LiquidCrystal_I2C.h>  // Biblioteca para o display LCD com interface I2C
#include "DHT.h"                // Biblioteca para o sensor DHT11
#include <EEPROM.h>             // Biblioteca para leitura e escrita na EEPROM
#include <RTClib.h>             // Biblioteca para o Relógio em Tempo Real (RTC)
#include <Wire.h>               // Biblioteca para comunicação I2C
#include "termometro.h"         // Biblioteca externa para funções relacionadas ao termômetro
#include "raio.h"               // Biblioteca externa para funções relacionadas à luminosidade
#include "gota.h"               // Biblioteca externa para funções relacionadas à umidade

// Definição de variáveis e pinos
int ValorLDR;               // Armazena a leitura do sensor LDR
int IntensidadeLuz;        // Transforma a leitura do LDR em uma escala de 0 a 100
int pinoLDR = A0;          // Pino analógico para ler o LDR
int buzzerPin = 7;         // Pino para o buzzer
int ledRedTemp = 13;       // Pino para o LED de temperatura
int ledYellowLumi = 12;    // Pino para o LED de luminosidade
int ledGreenHumi = 11;     // Pino para o LED de umidade

LiquidCrystal_I2C lcd(0x27, 16, 2); // Inicializa o display LCD com endereço 0x27 e 16 colunas e 2 linhas

#define DHTPIN 2             // Pino digital para o sensor DHT11
#define DHTTYPE DHT11        // Define o tipo de sensor DHT
#define UTC_OFFSET + 0       // Deslocamento do fuso horário em horas
#define SERIAL_OPTION 0      // Opção de serial (não usada no código)

int lastLoggedMinute = -1;  // Armazena o último minuto em que os dados foram registrados

RTC_DS1307 RTC;            // Objeto para o Relógio em Tempo Real
DHT dht(DHTPIN, DHTTYPE);  // Objeto para o sensor DHT11

// Configuração da EEPROM
const int maxRecords = 100;          // Número máximo de registros na EEPROM
const int recordSize = 12;           // Tamanho de cada registro em bytes
int startAddress = 0;                // Endereço inicial na EEPROM
int endAddress = maxRecords * recordSize; // Endereço final na EEPROM
int currentAddress = 0;              // Endereço atual para escrita na EEPROM

// Função para obter o próximo endereço disponível na EEPROM
void getNextAddress() {
    currentAddress += recordSize;
    if (currentAddress >= endAddress) {
        currentAddress = 0; // Volta para o começo se atingir o limite
    }
}

// Função para exibir os registros armazenados na EEPROM
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
        if (timeStamp > 0 && timeStamp < 0xFFFFFFFF) { // Verifica se o timestamp é válido
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

void setup() {
    lcd.init();                  // Inicializa o display LCD
    lcd.backlight();            // Liga a luz de fundo do display LCD
    lcd.clear();                // Limpa o display LCD
    dht.begin();                // Inicializa o sensor DHT11
    RTC.begin();                // Inicializa o Relógio em Tempo Real
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__))); // Ajusta o relógio para o momento da compilação
    Serial.begin(9600);         // Inicializa a comunicação serial a 9600 bps
    pinMode(pinoLDR, INPUT);    // Define o pino LDR como entrada
    EEPROM.begin();            // Inicializa a EEPROM
    pinMode(buzzerPin, OUTPUT); // Define o pino do buzzer como saída
    pinMode(ledRedTemp, OUTPUT); // Define o pino do LED de temperatura como saída
    pinMode(ledYellowLumi, OUTPUT); // Define o pino do LED de luminosidade como saída
    pinMode(ledGreenHumi, OUTPUT); // Define o pino do LED de umidade como saída
    digitalWrite(ledRedTemp, LOW); // Garante que o LED de temperatura esteja apagado
    digitalWrite(ledYellowLumi, LOW); // Garante que o LED de luminosidade esteja apagado
    digitalWrite(ledGreenHumi, LOW); // Garante que o LED de umidade esteja apagado
}

// Função para controlar a luminosidade com base na leitura do LDR
int ControleLuminosidade(int ValorLDR) {
    IntensidadeLuz = map(ValorLDR, 205, 958, 0, 100); // Mapeia a leitura do LDR para uma escala de 0 a 100
    if (IntensidadeLuz < 0) {
        IntensidadeLuz = 0;
    } else if (IntensidadeLuz > 100) {
        IntensidadeLuz = 100;
    }
    return IntensidadeLuz;
}

// Função para verificar se uma grandeza está dentro dos limites especificados
bool MedeLimite(int grandeza, int minimo, int maximo) {
    return (grandeza >= minimo && grandeza <= maximo);
}

void loop() {
    DateTime now = RTC.now();  // Obtém o horário atual do RTC

    // Calcula o deslocamento do fuso horário
    int offsetSeconds = UTC_OFFSET * 3600; // Converte horas para segundos
    now = now.unixtime() + offsetSeconds; // Adiciona o deslocamento ao tempo atual
    DateTime adjustedTime = DateTime(now); // Converte o tempo ajustado para DateTime

    // Exibe os registros armazenados na EEPROM (para depuração)
    get_log();

    // Verifica se o minuto atual é diferente do minuto do último registro
    if (adjustedTime.minute() != lastLoggedMinute) {
        float temperature = dht.readTemperature(); // Lê a temperatura do sensor DHT
        float humidity = dht.readHumidity();       // Lê a umidade do sensor DHT
        ValorLDR = analogRead(pinoLDR);           // Lê o valor do LDR
        int luminosidade = ControleLuminosidade(ValorLDR); // Converte a leitura do LDR para luminosidade
        lastLoggedMinute = adjustedTime.minute(); // Atualiza o minuto do último registro

        // Exibe uma mensagem de verificação no LCD
        lcd.clear();
        lcd.print("Checando padrao");
        lcd.setCursor(0, 1);
        lcd.print("das grandezas...");
        delay(3000);
        lcd.clear();

        // Verifica os limites para luminosidade, temperatura e umidade
        bool teste_luminosidade = MedeLimite(luminosidade, 0, 30);
        bool teste_temperature = MedeLimite(temperature, 15, 25);
        bool teste_humidity = MedeLimite(humidity, 30, 50);
        delay(100);

        int delayTotal = 12000; // Tempo total de verificação
        for (int i = 0; i < 5; i++) {
            noTone(buzzerPin); // Desliga o buzzer

            verifyHumidity(humidity); // Função externa para verificar umidade
            verifyLuminosity(luminosidade); // Função externa para verificar luminosidade
            verificaTemperatura(temperature); // Função externa para verificar temperatura

            delay(delayTotal / 10); // Espera um tempo antes da próxima verificação

            // Atualiza o display LCD e os LEDs de acordo com os limites
            if (!teste_luminosidade) {
                lcd.setCursor(6, 0);
                lcd.print("      ");
                lcd.setCursor(6, 1);
                lcd.print("      ");
                tone(buzzerPin, 500); // Emite um tom no buzzer
                digitalWrite(ledYellowLumi, HIGH); // Acende o LED de luminosidade
            }
            if (!teste_temperature) {
                lcd.setCursor(0, 0);
                lcd.print("      ");
                lcd.setCursor(0, 1);
                lcd.print("      ");
                tone(buzzerPin, 200); // Emite um tom no buzzer
                digitalWrite(ledRedTemp, HIGH); // Acende o LED de temperatura
            }
            if (!teste_humidity) {
                lcd.setCursor(12, 0);
                lcd.print("    ");
                lcd.setCursor(12, 1);
                lcd.print("    ");
                tone(buzzerPin, 700); // Emite um tom no buzzer
                digitalWrite(ledGreenHumi, HIGH); // Acende o LED de umidade
            }

            delay(delayTotal / 10); // Espera um tempo antes da próxima verificação

            // Atualiza os valores das medições
            temperature = dht.readTemperature();
            humidity = dht.readHumidity();
            ValorLDR = analogRead(pinoLDR);
            luminosidade = ControleLuminosidade(ValorLDR);
            teste_luminosidade = MedeLimite(luminosidade, 0, 30);
            teste_temperature = MedeLimite(temperature, 15, 25);
            teste_humidity = MedeLimite(humidity, 30, 50);
        }
        // Desliga os LEDs e o buzzer após a verificação
        digitalWrite(ledRedTemp, LOW);
        digitalWrite(ledYellowLumi, LOW);
        digitalWrite(ledGreenHumi, LOW);
        noTone(buzzerPin);

        // Armazena os dados na EEPROM se algum valor estiver fora dos limites
        if (!teste_luminosidade || !teste_temperature || !teste_humidity) {
            int tempInt = (int)(temperature * 100); // Converte a temperatura para inteiro
            int humiInt = (int)(humidity * 100);    // Converte a umidade para inteiro

            // Armazena os dados na EEPROM
            EEPROM.put(currentAddress, now.unixtime());
            EEPROM.put(currentAddress + 4, tempInt);
            EEPROM.put(currentAddress + 6, humiInt);
            EEPROM.put(currentAddress + 8, luminosidade);
            Serial.println("Grandezas foras dos padrões");

            getNextAddress(); // Avança para o próximo endereço na EEPROM
        }

        // Verifica se a leitura do sensor falhou
        if (isnan(temperature) || isnan(humidity)) {
            Serial.println(F("Failed to read from DHT sensor!"));
            return;
        }
    }

    // Exibe a data e hora atual no LCD
    lcd.setCursor(0, 0);
    lcd.print("DATA: ");
    lcd.print(adjustedTime.day() < 10 ? "0" : ""); // Adiciona zero à esquerda se o dia for menor que 10
    lcd.print(adjustedTime.day());
    lcd.print("/");
    lcd.print(adjustedTime.month() < 10 ? "0" : ""); // Adiciona zero à esquerda se o mês for menor que 10
    lcd.print(adjustedTime.month());
    lcd.print("/");
    lcd.print(adjustedTime.year());
    lcd.setCursor(0, 1);
    lcd.print("HORA: ");
    lcd.print((adjustedTime.hour() + 3) < 10 ? "0" : ""); // Adiciona zero à esquerda se a hora for menor que 10
    lcd.print(adjustedTime.hour());
    lcd.print(":");
    lcd.print(adjustedTime.minute() < 10 ? "0" : ""); // Adiciona zero à esquerda se o minuto for menor que 10
    lcd.print(adjustedTime.minute());
    lcd.print(":");
    lcd.print(adjustedTime.second() < 10 ? "0" : ""); // Adiciona zero à esquerda se o segundo for menor que 10
    lcd.print(adjustedTime.second());

    delay(1000); // Espera 1 segundo antes de atualizar o LCD
    lcd.clear(); // Limpa o display LCD
}
