#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include <Adafruit_AM2315.h>

#define MAXDO   27
#define MAXCS   33
#define MAXCLK  15

float Temp_F;
float temperature, humidity;

Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);
Adafruit_AM2315 am2315;

void setup()
{
  Serial.begin(9600);

  am2315.begin();
}
 

void loop() 
{

  am2315.readTemperatureAndHumidity(&temperature, &humidity);

  Temp_F = ((temperature * (9/5))+ 32);
   
  Serial.print("31855 Temp F = ");
  Serial.println(thermocouple.readFahrenheit());

  Serial.print("AM 2315 Temp F = "); 
  Serial.println(Temp_F);

  Serial.println(" ");
 
  delay(2000);

 }