

void checkHic() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if ( isnan(h) || isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    isWifiOn = true;
  }
  else {
    isWifiOn = false;
      dht_temp = dht.computeHeatIndex(t, h, false);
  }
}
