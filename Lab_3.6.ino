
#include "freertos/semphr.h"

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
// Globals

static SemaphoreHandle_t mutex;// creating a mutex handle
static int shared_var = 0;
//*****************************************************************************
// Tasks
// Increment shared variable (the wrong way)
void incTask(void *parameters) {
  int local_var;
  // Loop forever
  
   while (1) {
    // Roundabout way to do "shared_var++" randomly and poorly
  local_var = shared_var;
  local_var++;
  vTaskDelay(random(100, 500) / portTICK_PERIOD_MS);
  shared_var = local_var;
   
  // Print out new shared variable
  Serial.println(shared_var);
}
 xSemaphoreGive(mutex);// Release the mutex to inform the task has exitted the critical section
}
//*****************************************************************************
// Main (runs as its own task with priority 1 on core 1)
void setup() {
          
    randomSeed(analogRead(0));// Hack to kinda get randomness
    Serial.begin(115200);// Configure Serial
    vTaskDelay(1000 / portTICK_PERIOD_MS);// Wait a moment to start (so we don't miss Serial output)
    Serial.println();
    Serial.println("---FreeRTOS Race Condition Demo---");

mutex = xSemaphoreCreateMutex();// Creating the mutex prior to the starting of the tasks


xSemaphoreTake(mutex, portMAX_DELAY); // Taking the mutex when starting the task
// Start task 1
xTaskCreatePinnedToCore(incTask,
        "Increment Task 1",
        1024,
        NULL,
        1,
        NULL,
        app_cpu);

xSemaphoreTake(mutex, portMAX_DELAY); // Taking the mutex when starting the task
// Start task 2
xTaskCreatePinnedToCore(incTask,
        "Increment Task 2",
        1024,
        NULL,
        1,
        NULL,
        app_cpu);

// Delete "setup and loop" task
vTaskDelete(NULL);
}
void loop() {
// Execution should never get here
}
