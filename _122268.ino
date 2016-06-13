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

#define DHTPIN 6
#define DHTTYPE DHT11
#define LEDPIN 2
#define NUMPIXELS 1
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                         SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID       "406"          // cannot be longer than 32 characters!
#define WLAN_PASS       "perry1613"
#define WLAN_SECURITY   WLAN_SEC_WPA2
#define IDLE_TIMEOUT_MS  1000      // Amount of time to wait (in milliseconds) with no data 

#define WEBSITE      "www.kma.go.kr"
#define WEBPAGE      "/wid/queryDFSRSS.jsp?zone=1121573000"
#define BUFSIZE 20

int dim;
DHT dht(DHTPIN, DHTTYPE);
bool isWifiOn = false;
float wifi_temp = 0;
float dht_temp = 0;
float temp = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
uint32_t ip;

void setup() {
  Serial.begin(9600);
  pixels.begin();
  if (!cc3000.begin()) {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
  }
  dht.begin();
}

void loop()
{
  getData();
  checkHic();
  
  if (isWifiOn) {
    temp = wifi_temp;
    Serial.println("wifi");
  }
  else {
    temp = dht_temp;
    Serial.println("dht");
  }
  if ( temp < 9.0) coldLed();
  else if ( temp < 16.0) coolLed();
  else if ( temp < 22.0) fineLed();
  else if ( temp < 26.0) warmLed();
  else if ( temp >= 26.0) hotLed();
  
  delay(600000);
}
