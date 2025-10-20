#include <Arduino.h>

// ==================== CONFIGURAÇÃO ====================
const int GAS_ANALOG_PIN  = 33;   // Pino analógico do ESP-12F OAK
const int GAS_DIGITAL_PIN = 14;   // Pino digital de alerta do MQ-2
const int CALIBRATION_TIME = 10000; // 10s para calibrar no ar limpo

int baseline = 0;

// ==================== SETUP ====================
void setup() {
  Serial.begin(115200);
  pinMode(GAS_ANALOG_PIN, INPUT);
  pinMode(GAS_DIGITAL_PIN, INPUT);

  Serial.println("MQ-2 Teste com Calibração...");
  Serial.println("Mantenha o sensor em ar limpo...");

  // ==================== CALIBRAÇÃO ====================
  long sum = 0;
  unsigned long start = millis();
  while (millis() - start < CALIBRATION_TIME) {
    sum += analogRead(GAS_ANALOG_PIN);
    delay(100);
  }
  baseline = sum / (CALIBRATION_TIME / 100); // média
  Serial.print("Calibração concluída. Valor base: ");
  Serial.println(baseline);
}

// ==================== LOOP ====================
void loop() {
  int analogValue = analogRead(GAS_ANALOG_PIN);
  int digitalValue = digitalRead(GAS_DIGITAL_PIN);

  // Ajusta a leitura pelo baseline
  int adjustedValue = analogValue - baseline;
  if(adjustedValue < 0) adjustedValue = 0;

  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print(" | Ajustado: ");
  Serial.print(adjustedValue);
  Serial.print(" | Digital: ");
  Serial.println(digitalValue);

  delay(1000);
}
