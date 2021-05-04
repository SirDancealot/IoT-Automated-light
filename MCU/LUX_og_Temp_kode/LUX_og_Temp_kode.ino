#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266WebServer.h>   // Include the WebServer library
#include <ESP8266mDNS.h>        // Include the mDNS library

ESP8266WiFiMulti wifiMulti;

#include <DHT.h>                // Include library for the temp and humidity
#define DHTTYPE DHT11 
DHT dht(5, DHTTYPE);

//Wifi id and password
const char* ssid = "iPhone";
const char* password = "12345678";

//Set light source pin
const byte LED = 2; //D4 pin
const char* serverName = "http://api.mj-software.dk/data";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;
float temp = 0;
int lux = 0;
float voltage = 0;
int humidity = 0;
const int LDR = A0; //analog signal

void setup()  {
Serial.begin(9600);
pinMode(LED, OUTPUT);
Serial.println("Temperatur, Humidity & Lux\n\n");
delay(100);

 wifiMulti.addAP(ssid, password);
  Serial.println("Connecting");
  while(wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  pinMode(LED, OUTPUT); 
  digitalWrite(LED,LOW);
  dht.begin();
}

void loop()
{
   // Send http POST -----------------------------
 if ((millis() - lastTime) > timerDelay) {
    
    //Wifi
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

  
//Code for temp (DHT11)
temp = dht.readTemperature();
Serial.print("Temperature = ");
Serial.print(temp);
Serial.println(" °C  ");
delay(300);

//Code for humidity (DHT11)
humidity = dht.readHumidity();
Serial.print("Humidity = ");
Serial.print(humidity);
Serial.println(" %\n ");
delay(300);

//Code for Lux (LDR sensor)
lux = analogRead(A0);//read the input on analog pin 0
voltage = lux*(3.3/1023); //Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 3.3V)
Serial.print("Lux = ");
Serial.print(voltage);// print out the value you read
Serial.println(" V\n  ");
analogWrite(LED, lux);
 
  Serial.println();
  
  delay(100); //delay med 100 ms
      
          // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      char *httpPostData;
      httpPostData = (char *)calloc(sizeof(char), 50);
      sprintf(httpPostData,"?temp=%f&lux=%f&humidity=%d",temp,voltage, humidity);
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

    String serverPath = serverName + String("/latest/lux");

    httpget.begin(serverPath.c_str());

    int httpgetResponseCode = httpget.GET();

     if (httpgetResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpgetResponseCode);
        String payload = httpget.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpgetResponseCode);
      }

//      if(lux<500){
//        digitalWrite(led,HIGH);
//      } else {
//        digitalWrite(led,LOW);
//      }

    lastTime = millis();
  }
}
