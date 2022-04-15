//go to https://github.com/adafruit/Adafruit_NeoPixel to find neopixel library installation instructions
#include <Adafruit_NeoPixel.h>


int bottomS1 = A0;
int bottomS2 = A1;
int bottomN1 = A2;
int bottomN2 = A3;
int topS1 = A4;
int topS2 = A5;

int val[6];

int northThresh = 400;
int southThresh = 320;

#define PIN 6
#define NUMPIXELS 6
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

  pixels.begin();
  pixels.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  val[0] = analogRead(bottomS1);
  val[1]= analogRead(bottomS2);
  val[2] = analogRead(topS1);
  val[3] = analogRead(topS2);
  val[4] = analogRead(bottomN1);
  val[5] = analogRead(bottomN2);

  for (int i = 0; i < 4; i++)
  {
    Serial.print("val ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(val[i]);
    if (val[i] < southThresh)
    {
      //light up corresponding led
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    }
    else if (val[i] > northThresh)
    {
      //light it up in a bad color
      pixels.setPixelColor(i, pixels.Color(255,0,0));
    }
    else
    {
      //turn off led
      pixels.setPixelColor(i, pixels.Color(0,0,0));
    }
  }

  for (int i = 4; i < 6; i++)
  {
    Serial.print("val ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(val[i]);
    if (val[i] > northThresh)
    {
       //light up corresponding led
       pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    }
    else if (val[i] < southThresh)
    {
      //light it up in a bad color
      pixels.setPixelColor(i, pixels.Color(255,0,0));
    }
    else
    {
      //turn off led
      pixels.setPixelColor(i, pixels.Color(0,0,0));
    }
  }

  Serial.print("\n");
  pixels.show();
  delay(500);

}
