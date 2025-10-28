#include <Arduino.h>

const int GAS_ANALOG_PIN = 33;
const int CALIBRATION_TIME = 10000;

int baseline = 0;

void setup() {
  Serial.begin(115200);
  pinMode(GAS_ANALOG_PIN, INPUT);

  Serial.println("Iniciando teste com MQ-2...");

  long sum = 0;
  unsigned long start = millis();
  while (millis() - start < CALIBRATION_TIME) {
    sum += analogRead(GAS_ANALOG_PIN);
    delay(100);
  }

  baseline = sum / (CALIBRATION_TIME / 100);
  Serial.print("Calibracao concluida. Valor base: ");
  Serial.println(baseline);
}

void loop() {
  int analogValue = analogRead(GAS_ANALOG_PIN);
  int adjustedValue = analogValue - baseline;
  if (adjustedValue < 0) adjustedValue = 0;

  Serial.print("Leitura: ");
  Serial.print(analogValue);
  Serial.print(" | Corrigida: ");
  Serial.println(adjustedValue);

  delay(1000);
}
