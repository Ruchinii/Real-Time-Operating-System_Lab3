#include "freertos/FreeRTOS.h"


static const int delay_ms = 500;

void setup() {
  // put your setup code here, to run once:
    pinMode(LED_BUILTIN , OUTPUT);
  
  
}
void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(LED_BUILTIN,HIGH);
  vTaskDelay(delay_ms/portTICK_PERIOD_MS);
  digitalWrite(LED_BUILTIN,LOW);
  vTaskDelay( delay_ms/portTICK_PERIOD_MS);
}
