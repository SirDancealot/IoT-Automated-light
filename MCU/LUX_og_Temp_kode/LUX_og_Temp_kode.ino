const int cInput = A0; //analog signal
const int cSelectPin = 15; //Pin som vælger mellem CX og CY
int inputValue;

void setup()  {
  Serial.begin(9600);
  pinMode(cSelectPin, OUTPUT); //sætter pin D8 som output

void loop() 
{
  digitalWrite(cSelectPin, LOW); //pin D8 lav, CX bliver valgt
  inputValue = analogRead(cInput); //læser analog værdi fra CX
  Serial.print(String(inputValue) + "\t"); //printer værdi ud
  
  digitalWrite(cSelectPin, HIGH); //pin D8 høj, CY bliver valgt
  inputValue = analogRead(cInput); //læser analog værdi fra CY
  Serial.print(String(inputValue) + "\t"); //printer værdi ud
  
  Serial.println();
  
  delay(100); //delay med 100 ms
}
