
void coldLed() {
  //-5 ~ 9도
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 255) );
    pixels.show();
  }
}

void coolLed() {
  //10 ~ 16도
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255) );
    pixels.show();
  }
}

void fineLed() {
  //17 ~ 22도
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 69, 0) );
    pixels.show();
  }
}

void warmLed() {
  //23 ~ 26도
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 0) );
    pixels.show();
  }
}

void hotLed() {
  //27도 이상
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0) );
    pixels.show();
  }
}
