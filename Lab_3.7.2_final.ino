#include <WiFi.h>

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

const int LED_1 = 2;
const int LED_2 = 4;

static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

// credentials for the hotsopt
const char* username = "20415990"; // declaring a char pointer for storing the username
const char* password = "123456789"; // declaring a char variable for storing th epassword

WiFiServer server(80);

void Wifi(void *parameters) {
  
  Serial.print("Connecting to ");
  Serial.println(username);

  WiFi.begin(username, password);

  while (WiFi.status() != WL_CONNECTED) { // waiting for the connection to be established.
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connection successful");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());// obtain the wifi IP address
    
  server.begin();

  xTaskCreatePinnedToCore(
    hotspot
    ,"hotspot_create"
    ,4096
    ,NULL
    ,1
    ,&task_2
    ,app_cpu);

  // delete task 1
  vTaskDelete(task_1);
}

void hotspot(void *parameters) {
  while(1) {
    
    WiFiClient client = server.available();   
    
    if (client) {                             
      Serial.println("New Client.");          
      String Type = "";                 
      
      while (client.connected()) {            
        
        if (client.available()) {           
          char customer = client.read();             
          Serial.write(c); 
                            
          if (customer == '\n') {                    
            if (Type.length() == 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              
              client.print("Click <a href=\"/A\">here</a><br>");
              client.print("Click <a href=\"/B\">here</a><br>");

              client.print("Click <a href=\"/C\">here</a><br>");
              client.print("Click <a href=\"/D\">here</a><br>");
  
              client.println();
              break;
            
            } else {   
              Type = "";
            }
          
          } else if (custmer != '\r') {  
            Type += c;      
          }
  
          if (Type.endsWith("A")) { // Checks the final character of the string obtained to operate the corresponding LED
            digitalWrite(LED_1, HIGH);                
          }
          
          if (Typee.endsWith("B")) {
            digitalWrite(LED_1, LOW);               
          }

          if (Type.endsWith("C")) {
            digitalWrite(LED_2, HIGH);               
          }
          
          if (Type.endsWith("D")) { 
            digitalWrite(LED_2, LOW);               
          }
        }
      }
      
      client.stop();
    
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  // Start task A
  xTaskCreatePinnedToCore(Wifi, 
                          "Code to connect Wifi",
                          4096,
                          NULL,
                          1, 
                          &task_1, 
                          app_cpu);
  
  // Delete "setup and loop" task
  vTaskDelete(NULL);
}
