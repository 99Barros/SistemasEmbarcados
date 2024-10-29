# N1 Sistemas Embarcados  
**Repositório Dedicado a N1 de Sistemas Embarcados de EC5 (2024)**

## Data Logger - Projeto com Arduino

### Descrição
O **Data Logger** é um dispositivo capaz de monitorar e registrar dados ambientais, como **temperatura**, **umidade** e **luminosidade**, em intervalos regulares de tempo. Utilizando sensores de temperatura e umidade, um sensor de luz e um relógio de tempo real (**RTC**), os dados são exibidos em um display **LCD** e podem ser armazenados na memória **EEPROM do Arduino UNO** para posterior análise. O projeto é alimentado por uma bateria de 9V, garantindo sua mobilidade e funcionamento autônomo.

---

### Lista de Materiais

- **1 MCU (Atmega 328P)** - Arduino Uno R3: O cérebro do sistema, responsável por processar os sinais dos sensores e exibir as informações.
- **1 LDR (Light Dependent Resistor)** + Resistor 10KOhm: Sensor de luminosidade que mede a intensidade da luz ambiente.
- **1 DHT-11**: Sensor de temperatura e umidade.
- **1 LCD 16x2 - I2C**: Tela LCD para exibir as leituras de temperatura, umidade e luz.
- **1 Bateria de 9V** + suporte: Fonte de alimentação para o Arduino.
- **1 RTC (Real Time Clock)**: Relógio de tempo real, que mantém a data e hora atualizadas, mesmo quando o sistema é desligado.
- Protoboard, jumpers, LEDs e resistores: Usados para montar o circuito de forma modular e simples.

---

### Especificações Técnicas

#### Arduino Uno R3 (Atmega 328P)
- **Tensão de operação**: 5V  
- **Memória Flash**: 32 KB  
- **Velocidade do clock**: 16 MHz  

#### Sensor DHT-11
- **Faixa de medição de temperatura**: 0-50°C, precisão de ±2°C  
- **Faixa de umidade**: 20-80%, precisão de ±5%  

#### Sensor LDR
- **Resistência**: Varia de acordo com a luz ambiente  
- Uso com resistor de 10KOhm para formar um divisor de tensão  

#### Display LCD 16x2 - I2C
- **Alimentação**: 5V  
- Comunicação via protocolo I2C (endereçamento padrão 0x27)  

#### RTC DS3231 (Real Time Clock)
- **Precisão**: ±2 ppm a 0-40°C  
- Bateria interna para manter a hora após desligamento  

#### Fonte de Alimentação
- **Bateria de 9V**  
- Conversão de tensão via regulador interno do Arduino para 5V  

---

### Diagrama Elétrico

*(O diagrama elétrico ilustra a conexão entre todos os componentes do projeto. Conecte os dispositivos conforme o esquema abaixo)*

---

### Manual de Operação

1. **Montagem**: Conecte todos os componentes de acordo com o diagrama elétrico. Use o Arduino Uno como base para a conexão dos sensores (DHT-11, LDR), o display LCD e o RTC.
   
2. **Carregar o Código**: Utilize a IDE Arduino para programar o Arduino Uno. Faça o upload do código que realiza a leitura dos sensores, exibe os dados no LCD e registra a data e hora com o RTC.
   
3. **Fonte de Energia**: Insira a bateria de 9V no suporte e conecte ao Arduino. O sistema iniciará a coleta de dados automaticamente.
   
4. **Visualização dos Dados**: A cada ciclo de leitura, os valores de temperatura, umidade e luminosidade serão exibidos no LCD em tempo real.
   
5. **Desligamento e Armazenamento**: Quando a bateria estiver fraca, desconecte o suporte da placa. O RTC continuará a contar o tempo graças à sua bateria interna.
   
6. **Manutenção**: Troque a bateria do projeto quando o display LCD ou os sensores não funcionarem corretamente devido à falta de energia.

---
