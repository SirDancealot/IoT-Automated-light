#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

const char* serverName = "http://mj-software.dk/LightAutomation";

unsigned long timerDelay = 5000;
float temp, lux;

void setup() {
  Serial.begin(9600); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
 // Send http POST -----------------------------
 if ((millis() - lastTime) > timerDelay) {
    
    //Wifi
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      //get temperature
      float reading = analogRead(kPinTemp);     //Analog pin reading output voltage by Lm35
      float temperatureC=kPinTemp/2.048;        //Finding the true centigrade/Celsius temperature
      
      //get lightLevel
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "temp="+ temp +"&lux="+ lux +"";           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
