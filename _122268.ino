#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <Adafruit_CC3000.h>
#include <Adafruit_CC3000_Server.h>
#include <ccspi.h>
#include <string.h>
#include "utility/debug.h"

#define DHTPIN 2
#define DHTTYPE DHT11
#define LEDPIN 6
#define NUMPIXELS 1
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                         SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID       "406"          // cannot be longer than 32 characters!
#define WLAN_PASS       "perry1613"
#define WLAN_SECURITY   WLAN_SEC_WPA2
#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 

#define WEBSITE      "www.kma.go.kr"
#define WEBPAGE      "/wid/queryDFSRSS.jsp?zone=1121573000"
#define BUFSIZE 20

int dim;
DHT dht(DHTPIN, DHTTYPE);
bool isWifiOn = false;
float temp = 0;
int delayval = 500;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
uint32_t ip;

void setup() {
  Serial.begin(9600);
  
  dht.begin();
  pixels.begin();
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    isWifiOn = false;
  }
}

void loop()
{
  if(!isWifiOn)
  {
    temp = checkHic();
    Serial.println(temp);
  }
  else getData();
  
  if ( temp < 9.0) coldLed();
  else if ( temp < 16.0) coolLed();
  else if ( temp < 22.0) fineLed();
  else if ( temp < 26.0) warmLed();
  else if ( temp >= 26.0) hotLed();
}
