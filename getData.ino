
void getData() {
  Serial.print(F("Attempting to connect to ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while (1);
  }
  Serial.println(F("Connected!"));

  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }

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
  Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 80);
  if (www.connected()) {
    www.fastrprint(F("GET "));
    www.fastrprint(WEBPAGE);
    www.fastrprint(F(" HTTP/1.1\r\n"));
    www.fastrprint(F("Host: ")); www.fastrprint(WEBSITE); www.fastrprint(F("\r\n"));
    www.fastrprint(F("\r\n"));
    www.println();
  }
  else {
    Serial.println(F("Connection failed"));
    return;
  }

  Serial.println(F("-------------------------------------"));

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
          wifi_temp = atof(buffer);
          break;
        }

        tagStart = true;
        memset(buffer, 0, sizeof(char) * BUFSIZE);
        continue;
      }

      if (tagStart || readValue) {
        buffer[strlen(buffer)] = c;
      }
      lastRead = millis();
    }
  }
  www.close();
  Serial.println(F("-------------------------------------"));
  Serial.println(F("\n\nDisconnecting"));
 // cc3000.disconnect();

  Serial.println(wifi_temp);
  
}
