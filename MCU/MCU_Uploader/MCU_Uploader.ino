#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266WebServer.h>   // Include the WebServer library
#include <ESP8266mDNS.h>        // Include the mDNS library

ESP8266WiFiMulti wifiMulti;

//Wifi id and password
const char* ssid = "Pouline";
const char* password = "lakimini";

//Set light source pin
const byte led = <insert pin>;

//Data input pins
const byte tempAnalog = <tempreture pin>;
const byte luxAnalog = <lux pin>;

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

  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}

void loop() {
  
 // Send http POST -----------------------------
 if ((millis() - lastTime) > timerDelay) {
    
    //Wifi
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      //get temperature
      float reading = analogRead(tempreture pin);     //Analog pin reading output voltage by Lm35
      temp=reading/2.048;                             //Finding the true centigrade/Celsius temperature
     
      //get lightLevel
      lux = analogRead(luxAnalog);
      
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
    } else {
      Serial.println("WiFi Disconnected");
    }

    // Send http GET -----------------------------
    HTTPClient httpget;
    
    String serverPath = serverName + "/latest/lux";

    httpget.begin(serverPath.c_str());

    int httpgetResponseCode = http.GET();

     if (httpgetResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpgetResponseCode);
        String payload = httpget.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }

      if(lux<500){
        digitalWrite(led,HIGH);
      } else {
        digitalWrite(led,LOW);
      }
    
    lastTime = millis();
  }
}
