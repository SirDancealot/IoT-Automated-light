#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266WebServer.h>   // Include the WebServer library
#include <ESP8266mDNS.h>        // Include the mDNS library
#include <DHT.h>
#define DHTTYPE DHT11 
DHT dht(5, DHTTYPE);


ESP8266WiFiMulti wifiMulti;


//Wifi id and password
const char* ssid = "iphone";
const char* password = "12345678";

//Set light source pin
const byte led = 4;


const char* serverName = "http://api.mj-software.dk/data";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;
float temp, lux;
float voltage = 0;
float humidity = 0;

const int LDR = A0; //analog signal
int inputValue;

void setup()  {
  Serial.begin(9600);
  dht.begin();
Serial.println("Temperatur and humidity\n\n");
delay(500);  
 // pinMode(cSelectPin, OUTPUT); //sætter pin D8 som output
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

void loop()
{
   // Send http POST -----------------------------
 if ((millis() - lastTime) > timerDelay) {
    
    //Wifi
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
       
  
temp = dht.readTemperature();
Serial.print("Temperature = ");
Serial.print(String(temp) + "\t"); //printer værdi ud
Serial.println(" C  ");
delay(300);

humidity = dht.readHumidity();
Serial.print("Humidity = ");
Serial.print(String(humidity) + "\t"); //printer værdi ud
Serial.println(" %  ");
delay(300);

lux = analogRead(LDR);//read the input on analog pin 0
voltage = lux*(3.3/1023.0); //Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
Serial.print(String(voltage) + "\t"); //printer værdi ud


    
  Serial.println();
  
  delay(100); //delay med 100 ms

      
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
