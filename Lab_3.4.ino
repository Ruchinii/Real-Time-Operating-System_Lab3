
#include "freertos/FreeRTOS.h"


// Use only core 1 for demo purposes

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif


const char msg[] = ""; 


static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;


void startTask1(void *parameter) { // Count number of characters in string
  int msg_len = strlen(msg); // Print string to Terminal
  while (1) {
    Serial.println();
    for (int i = 0; i < msg_len; i++) {
        Serial.print(msg[i]);
 }
        Serial.println();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}

void startTask2(void *parameter) {
     while (1) {
        Serial.print('*');
         vTaskDelay(100 / portTICK_PERIOD_MS);
}
}

void setup(){

xTaskCreatePinnedToCore(
       startTask1,//Function which runs the task
       "Print to Serial Monitor - Low Priority task",//Text name for the task
       1024,//Stack depth
       NULL, // Parameter passed to the task
       2, //Priority
       NULL,
       app_cpu);
          
xTaskCreatePinnedToCore(
       startTask2,//Function which runs the task
       "Print to Serial Monitor - High Priority task",//Text name for the task
       1024,//Stack depth
       NULL, // Parameter passed to the task
       1, //Priority
       NULL,
       app_cpu);
         
}
void loop(){
}
