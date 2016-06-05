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

#define DHTPIN 2            //DHT 11 핀
#define DHTTYPE DHT11

#define LEDPIN 6            //LED 핀
#define NUMPIXELS 10

#define ADAFRUIT_CC3000_IRQ   3  //WIFI 핀
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                         SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID       "makye"          // cannot be longer than 32 characters!
#define WLAN_PASS       "dkaghdkagh"
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 
// received before closing the connection.  If you know the server
// you're accessing is quick to respond, you can reduce this value.

// What page to grab!
#define WEBSITE      "www.kma.go.kr"
#define WEBPAGE      "/wid/queryDFSRSS.jsp?zone=1121573000"
#define WIFION  11
#define DHTON   22

#define BUFSIZE 20

int dim;
DHT dht(DHTPIN, DHTTYPE);

int delayval = 500;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);


uint32_t ip;

int mode;
float temp = 0;

void setup() {
  Serial.begin(9600); //디버그 시리얼

  dht.begin();
  Serial.println("DHT11 start");

  //pixels.begin();
  //  Serial.println("Neopixel start");

  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while (1);
  }

  // Optional SSID scan
  // listSSIDResults();

  Serial.print(F("Attempting to connect to ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while (1);
  }
  Serial.println(F("Connected!"));

  /* Wait for DHCP to complete */
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }

  /* Display the IP address DNS, Gateway, etc.
    while (! displayConnectionDetails()) {
    delay(1000);
    }*/

  ip = 0;
  // Try looking up the website's IP address
  Serial.print(WEBSITE); Serial.print(F(" -> "));
  while (ip == 0) {
    if (! cc3000.getHostByName(WEBSITE, &ip)) {
      Serial.println(F("Couldn't resolve!"));
    }
    delay(500);
  }

  cc3000.printIPdotsRev(ip);

  // Optional: Do a ping test on the website
  /*
    Serial.print(F("\n\rPinging ")); cc3000.printIPdotsRev(ip); Serial.print("...");
    replies = cc3000.ping(ip, 5);
    Serial.print(replies); Serial.println(F(" replies"));
  */

  /* Try connecting to the website.
     Note: HTTP/1.1 protocol is used to keep the server from closing the connection before all data is read.
  */
  Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 80);
  if (www.connected()) {
    www.fastrprint(F("GET "));
    www.fastrprint(WEBPAGE);
    www.fastrprint(F(" HTTP/1.1\r\n"));
    www.fastrprint(F("Host: ")); www.fastrprint(WEBSITE); www.fastrprint(F("\r\n"));
    www.fastrprint(F("\r\n"));
    www.println();
  } else {
    Serial.println(F("Connection failed"));
    return;
  }

  Serial.println(F("-------------------------------------"));

  /* Read data until either the connection is closed, or the idle timeout is reached. */
  unsigned long lastRead = millis();
  char buffer[BUFSIZE];
  boolean tagStart = false;
  boolean readValue = false;

  while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
    if (temp) {
      break;
    }
    
    while (www.available()) {
      char c = www.read(); 

      if (c == '>') {
        tagStart = false;
        if (strcmp(buffer, "temp") == 0) {
          readValue = true;
        }

        memset(buffer, 0, sizeof(char) * BUFSIZE);
        continue;
      }

      if (c == '<') {
        if (readValue) {
          readValue = false;

          // 첫번째 온도만 사용
          temp = atof(buffer);
          break;
        }

        tagStart = true;
        memset(buffer, 0, sizeof(char) * BUFSIZE);
        continue;
      }

      if (tagStart || readValue) {
        buffer[strlen(buffer)] = c;
      }

//      Serial.print(c);
      lastRead = millis();
    }
  }
  www.close();
  Serial.println(F("-------------------------------------"));

  /* You need to make sure to clean up after yourself or the CC3000 can freak out */
  /* the next time your try to connect ... */
  Serial.println(F("\n\nDisconnecting"));
  cc3000.disconnect();

  Serial.println(temp);
}

void loop()
{
  delay(1000);
  temp = checkHic();
  Serial.println(temp);

  /* if( checkHic() == 99 )
    {
     Serial.println("Wifi mode");
     mode=DHTON;
     temp = checkHic();
    }*/

  // if( temp < 9.0) coldLed();
  //else if( temp < 16.0) coolLed();
  //else if( temp < 22.0) fineLed();
  //else if( temp < 26.0) warmLed();
  //else if( temp >= 26.0) hotLed();
}
