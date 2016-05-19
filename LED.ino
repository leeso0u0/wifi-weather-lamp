
void coldLed() 
{
  //-5 ~ 9도
  for (int i = 0; i < NUMPIXELS; i++) 
  {
    pixels.setPixelColor(i, pixels.Color(64, 35, 16) );
    pixels.show();
  }
}

void coolLed() 
{
  //10 ~ 16도
  for (int i = 0; i < NUMPIXELS; i++) 
  {
    pixels.setPixelColor(i, pixels.Color(127, 76, 62) );
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
    pixels.setPixelColor(i, pixels.Color(106, 166, 255) );
    pixels.show();
  }
}

void hotLed() 
{
  //27도 이상
  for (int i = 0; i < NUMPIXELS; i++) 
  {
    pixels.setPixelColor(i, pixels.Color(46, 121, 235) );
    pixels.show();
  }
}
