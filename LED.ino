
void coldLed() 
{
  //-5 ~ 9도
  for (int i = 0; i < NUMPIXELS; i++) 
  {
    pixels.setPixelColor(i, pixels.Color(16, 35, 64) );
    pixels.show();
  }
}

void coolLed() 
{
  //10 ~ 16도
  for (int i = 0; i < NUMPIXELS; i++) 
  {
    pixels.setPixelColor(i, pixels.Color(62, 76, 127) );
    pixels.show();
  }
}

void fineLed() 
{
  //17 ~ 22도
  for (int i = 0; i < NUMPIXELS; i++) 
  {
    pixels.setPixelColor(i, pixels.Color(201, 201, 201) );
    pixels.show();
  }
}

void warmLed() 
{
  //23 ~ 26도
  for (int i = 0; i < NUMPIXELS; i++) 
  {
    pixels.setPixelColor(i, pixels.Color(255, 166, 106) );
    pixels.show();
  }
}

void hotLed() 
{
  //27도 이상
  for (int i = 0; i < NUMPIXELS; i++) 
  {
    pixels.setPixelColor(i, pixels.Color(235, 121, 46) );
    pixels.show();
  }
}
