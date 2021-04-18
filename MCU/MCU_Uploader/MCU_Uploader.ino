#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266WebServer.h>   // Include the WebServer library
#include <ESP8266mDNS.h>        // Include the mDNS library

ESP8266WiFiMulti wifiMulti;

const char* ssid = "Pouline";
const char* password = "lakimini";

const char* serverName = "http://api.mj-software.dk/data";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;
float temp, lux;

void setup() {
  Serial.begin(9600); 

  wifiMulti.addAP(ssid, password);
  Serial.println("Connecting");
  while(wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  temp = 50;
  lux = 100;
}

void loop() {
  
 // Send http POST -----------------------------
 if ((millis() - lastTime) > timerDelay) {
    
    //Wifi
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      //get temperature
      // float reading = analogRead(kPinTemp);     //Analog pin reading output voltage by Lm35
      // float temperatureC=kPinTemp/2.048;        //Finding the true centigrade/Celsius temperature

      //get lightLevel
      
      // Your Domain name with URL path or IP address with path
      
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      char *httpPostData;
      httpPostData = (char *)calloc(sizeof(char), 50);
      sprintf(httpPostData,"?temp=%f&lux=%f",temp,lux);
      http.begin(serverName + String(httpPostData));
      // Send HTTP POST request
      int httpResponseCode = http.POST("");
     
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
