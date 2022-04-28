// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif


void output_task_A(void *parameter){
  Serial.println("I am Task A I am Running on CORE_0");
  Serial.println(xPortGetCoreID());
  delay(2500);
}

void output_task_B(void *parameter){
  Serial.println("I am Task A I am Running on CORE_1");
  Serial.println(xPortGetCoreID());
  delay(2500);
}

void setup{

    xTaskCreatePinnedToCore(
    output_task_,
    "output_task_A"
   ,1024
   ,NULL
   ,1
   ,NULL
   app_cpu);


    xTaskCreatePinnedToCore(
    output_task_B,
    "output_task_B"
   ,1024
   ,NULL
   ,2
   ,NULL
   app_cpu);
    
}
