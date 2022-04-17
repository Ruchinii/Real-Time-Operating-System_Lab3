


// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int delay_ms = 500;



void blink_LED(void *pvParameters){//Task to blink internal LED
  while(1){
  digitalWrite(LED_BUILTIN,HIGH);
  vTaskDelay( delay_ms/portTICK_PERIOD_MS);
  digitalWrite(LED_BUILTIN,LOW);
  vTaskDelay( delay_ms/portTICK_PERIOD_MS);
  }
  
}





void setup() {
  // put your setup code here, to run once:

  pinmode(LED_BUILTIN,OUTPUT);

  xTaskCreatePinnedToCore(
    blink_LED
   ,"Blink Internal LED"
   ,1024
   ,NULL
   ,1
   ,NULL
   app_cpu);
   

}

void loop() {
  // put your main code here, to run repeatedly:

}
