#include <ThingSpeak.h>
#include <WiFi.h>
const char*ssid="mrunal";
const char *pwd="12345678";
const char *server="api.thingspeak.com";
const int sensor_pin =35;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */
const int motor_pin = 2;
WiFiClient client;
unsigned long myChannelNumber = 720563;
const char * myWriteAPIKey = "9X8PRVCQMIGY215T";

void setup() 
{
  Serial.begin(9600); /* Define baud rate for serial communication */
  delay(2000);
  pinMode(motor_pin,OUTPUT);
  //pinMode(sensor_pin,INPUT);
  WiFi.begin(ssid,pwd);
  ThingSpeak.begin(client);
}
  
void loop()
{
  float moisture_percentage;

 // moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );
 moisture_percentage = analogRead(sensor_pin);
  if(moisture_percentage < 2600)
  {
    Serial.println("motor oFF");
    digitalWrite(motor_pin,HIGH);
    }
     if(moisture_percentage > 2600)
  {
    Serial.println("motor oN");
    digitalWrite(motor_pin,LOW);
    }
  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.println(moisture_percentage);
//Serial.println();

ThingSpeak.writeField(myChannelNumber, 1,moisture_percentage, myWriteAPIKey);
  delay(17000);
 }
