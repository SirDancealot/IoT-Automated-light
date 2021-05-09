#include <Arduino_JSON.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266WebServer.h>   // Include the WebServer library
#include <ESP8266mDNS.h>        // Include the mDNS library
#include <string.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "iPhone";
const char* password = "12345678";
const char* serverName = "http://api.mj-software.dk/data/latest";
unsigned long lastTime = 0;


// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long timerDelay = 5000;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  { //Wait till connects
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  //Serial.println(WiFi.localIP()); //Use if using DHCP to know the IP
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
}
float arraydata[5];
void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);

  Serial.print("connecting to ");
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String serverPath = serverName;
    // Your Domain name with URL path or IP address with path
    http.begin(serverPath.c_str());

    // Send HTTP GET request
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      // Serial.print("HTTP Response code: ");
      // Serial.println(httpResponseCode);
      String payload = http.getString();
      //Serial.println(payload);
      Serial.println("\n");
      JSONVar myObject = JSON.parse(payload);
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }

      //Serial.print("JSON object = ");
      //Serial.println(myObject);

      // myObject.keys() can be used to get an array of all the keys in the object
      JSONVar keys = myObject.keys();

      for (int i = 0; i < keys.length(); i++) {
        JSONVar value = myObject[keys[i]];
        /*Serial.print(keys[i]);
          Serial.print(" = ");
          Serial.println(value);*/
        arraydata[i] = double(value);
      }
//Printing out the values to the Serial
      Serial.print("ID = ");
      Serial.println(arraydata[0]);
      Serial.print("Temp = ");
      Serial.println(arraydata[1]);
      Serial.print("Lux = ");
      Serial.println(arraydata[2]);
      Serial.print("Humidity = ");
      Serial.println(arraydata[3]);

      //displaying Temp in OLED
      display.clearDisplay();
      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      display.setCursor(0, 0);            // Start at top-left corner
      display.println("Temp: ");
      display.display();      // Show initial text
      sendFloatXY(arraydata[1],29,0);

      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      display.setCursor(1, 10);            // Start at top-left corner
      display.println("Lux: ");
      display.display();      // Show initial text
      sendFloatXY(arraydata[2],29,10);

      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      display.setCursor(1, 20);            // Start at top-left corner
      display.println("HUM: ");
      display.display();      // Show initial text
      sendFloatXY(arraydata[3],29,20);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  lastTime = millis();
}
/*void sendStringXY(char *string, int x, int y)
{
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(x, y);            // Start at top-left corner
  display.println(*string);
  display.display();      // Show initial text
}
*/
//function that prints a float variables out to the OLED
void sendFloatXY(float values, int x, int y)
{
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(x, y);            // Start at top-left corner
  display.println(values);
  display.display();      // Show initial text
}
