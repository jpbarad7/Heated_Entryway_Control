#define BLYNK_TEMPLATE_ID           "TMPL2sMz8hgur"
#define BLYNK_TEMPLATE_NAME         "Entryway Heater Control"
#define BLYNK_AUTH_TOKEN            "_S8m_n5oNYcnIOaTsRFHr1viCSjeReSo"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MAX31855.h"
#include <Adafruit_AM2315.h>

#define MAXDO   27
#define MAXCS   33
#define MAXCLK  15
#define Pump_SSR  32
#define PVH_SSR  14


float temperature, humidity;
int Ambient_Temp;
int Water_Temp;

Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);
Adafruit_AM2315 am2315;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "BR Guest";
char pass[] = "Pamma355!";

BLYNK_CONNECTED()
{
  Blynk.syncAll();
}

BLYNK_WRITE(V1)
{
  int Ambient_Temp = param.asInt();
  Blynk.virtualWrite(V0, Ambient_Temp);
}

BLYNK_WRITE(V2)
{
  int Water_Temp = param.asInt();
  Blynk.virtualWrite(V1, Water_Temp);
}

WidgetLED led1(V2);
WidgetLED led2(V3);


void setup()
{
  am2315.begin();
  Blynk.begin(auth, ssid, pass);
}
 

void loop() 
{
  Blynk.run();

  am2315.readTemperatureAndHumidity(&temperature, &humidity);
  Water_Temp = thermocouple.readFahrenheit();

  Ambient_Temp = ((temperature * 9/5) + 32);
   
  Blynk.virtualWrite(V0, Ambient_Temp);
  Blynk.virtualWrite(V1, Water_Temp);

  if (Water_Temp >= 90)
  {
    digitalWrite(Pump_SSR, HIGH);
    led1.on();
  }
  else 
  {
    digitalWrite(Pump_SSR, LOW);
    led1.off();
  }
  if (Ambient_Temp <= 32)
  {
    digitalWrite(PVH_SSR, HIGH);
    led2.on();
  } 
  else
  {
    digitalWrite(PVH_SSR, LOW);
    led2.off();
  } 
  
 }