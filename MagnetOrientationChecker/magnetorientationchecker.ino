//go to https://github.com/adafruit/Adafruit_NeoPixel to find neopixel library installation instructions
#include <Adafruit_NeoPixel.h>


int bottomN1 = A0;
int bottomS1 = A1;
int bottomS2 = A2;

int topS1 = A3;
int topS2 = A4;

//these two are digital pins
int topN1 = 2;
int topN2 = 3;

int val[7];

int northThresh = 400;
int southThresh = 320;

#define PIN 6
#define NUMPIXELS 2
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

  pinMode(topN1, INPUT);
  pinMode(topN2, INPUT);
  pixels.begin();
  pixels.clear();

  //set power led on
  pixels.setPixelColor(0, pixels.Color(255, 255, 255));
}

int check;
void loop() {
  // put your main code here, to run repeatedly:
  
  val[0] = analogRead(bottomN1);
  val[1] = analogRead(bottomS1);
  val[2]=  analogRead(bottomS2);
  val[3] = analogRead(topS1);
  val[4] = analogRead(topS2);
  val[5] = digitalRead(topN1);
  val[6] = digitalRead(topN2);

  Serial.print("BottomN1: ");
  Serial.println(val[0]);

  Serial.print("BottomS1: ");
  Serial.println(val[1]);

  Serial.print("BottomS2: ");
  Serial.println(val[2]);

  Serial.print("TopS1: ");
  Serial.println(val[3]);

  Serial.print("TopS2: ");
  Serial.println(val[4]);

  Serial.print("TopN1: ");
  Serial.println(val[5]);

  Serial.print("TopN2: ");
  Serial.println(val[6]);

  
  //check bottom 3 magnets orientation=
  check = 1;
  if (val[0] < northThresh)
  {
    check = 0;
  }

  if (val[1] > southThresh || val[2] > southThresh)
  {
    check = 0;
  }

  //check top magnets
  //only two magnets present, but orientation unknown
  //all we know is that they're opposite of each other
  if ( (val[3] > southThresh || val[4] > southThresh) &&
      (val[5] == 1 || val[6] == 1) )
  {
    check = 0;
  }
  
  if (check)
  {
    pixels.setPixelColor(1, pixels.Color(0, 255, 0));
  }
  else
  {
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  }
  Serial.print("\n");
  pixels.show();
  delay(500);

}
