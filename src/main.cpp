#include <Arduino.h>

const int mq2Analog = A0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Teste MQ2 iniciado!");
}

void loop() {
  int leitura = analogRead(mq2Analog);
  Serial.print("Leitura MQ2: ");
  Serial.println(leitura);
  delay(1000);
}
