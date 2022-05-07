// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int delay_ms_1 = 500;
static const int delay_ms_2 = 300;

int led_pin_1 = 2 // Connecting an external led to GPIO2
int led_pin_2 = 3 // Connecting an external led to GPIO3

void blink_LED_500(void *pvParameters){//Task to blink internal LED
  while(1){
  digitalWrite(LED_BUILTIN,HIGH);
  vTaskDelay( delay_ms_1/portTICK_PERIOD_MS);
  digitalWrite(LED_BUILTIN,LOW);
  vTaskDelay( delay_ms_1/portTICK_PERIOD_MS);
  }
  
  
}
void blink_LED_300(void *pvParameters){//Task to blink internal LED
  while(1){
  digitalWrite(led_pin_1,HIGH);
  vTaskDelay( delay_ms_2/portTICK_PERIOD_MS);
  digitalWrite(led_pin_1,LOW);
  vTaskDelay( delay_ms_2/portTICK_PERIOD_MS);
  }
  
  
}




void setup() {
  // put your setup code here, to run once:

  pinmode(LED_BUILTIN,OUTPUT);

  xTaskCreatePinnedToCore(
    blink_LED_500
   ,"Blink Internal LED with 500 ms delay"
   ,1024
   ,NULL
   ,1
   ,NULL
   app_cpu);

    xTaskCreatePinnedToCore(
    blink_LED_300
   ,"Blink Internal LED with 300 ms delay"
   ,1024
   ,NULL
   ,1
   ,NULL
   app_cpu);
   

}



void loop() {
  // put your main code here, to run repeatedly:

}
