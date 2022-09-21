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

int northThresh = 360;
int southThresh = 350;

#define PIN 6
#define NUMPIXELS 2
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int count;
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
  pixels.setPixelColor(0, pixels.Color(32, 32, 32));
  delay(500);
}

int check;

int BN1Check;
int BS1Check;
int BS2Check;
int TS1Check;
int TS2Check;
int TN1Check;
int TN2Check;


void loop() {
  // put your main code here, to run repeatedly:
  BN1Check = 1;
  BS1Check = 1;
  BS2Check = 1;
  TS1Check = 1;
  TS2Check = 1;
  TN1Check = 1;
  TN2Check = 1;
  
  val[0] = analogRead(bottomN1);
  val[1] = analogRead(bottomS1);
  val[2]=  analogRead(bottomS2);
  val[3] = analogRead(topS1);
  val[4] = analogRead(topS2);
  val[5] = digitalRead(topN1);
  val[6] = digitalRead(topN2);
  
  //check bottom 3 magnets orientation=
  check = 1;
  if (val[0] > southThresh)
  {
    check = 0;
    BN1Check = 0;
  }

  if (val[1] < northThresh || val[2] < northThresh)
  {
    check = 0;
    if (val[1] < northThresh)
    BS1Check = 0;
    if (val[2] < northThresh)
    BS2Check = 0;
  }

  //check top magnets
  //only two magnets present, but orientation unknown
  //all we know is that they're opposite of each other
  if ( (val[3] < northThresh || val[4] < northThresh) &&
      (val[5] == 1 || val[6] == 1) )
  {
    check = 0;
    if (val[3] < northThresh) TS1Check = 0;
    if (val[4] < northThresh) TS2Check = 0;
    if (val[5] == 1) TN1Check = 0;
    if (val[6] == 1) TN2Check = 0;
  }
  
  if (check)
  {
    pixels.setPixelColor(1, pixels.Color(0, 32, 0));
  }
  else
  {
    pixels.setPixelColor(1, pixels.Color(32, 0, 0));
  }
  Serial.print("\n");
  pixels.show();
  delay(500);

  Serial.print("BottomN1: ");
  Serial.print(val[0]);
  if (BN1Check)
    Serial.println(" Pass!");
  else
    Serial.println(" Fail");
    
  Serial.print("BottomS1: ");
  Serial.print(val[1]);
  if (BS1Check)
    Serial.println(" Pass!");
  else
    Serial.println(" Fail");
    
  Serial.print("BottomS2: ");
  Serial.print(val[2]);
  if (BS2Check)
    Serial.println(" Pass!");
  else
    Serial.println(" Fail");
    
  Serial.print("TopS1: ");
  Serial.print(val[3]);
  if (TS1Check)
    Serial.println(" Pass!");
  else
    Serial.println(" Fail");
    
  Serial.print("TopS2: ");
  Serial.print(val[4]);
  if (TS2Check)
    Serial.println(" Pass!");
  else
    Serial.println(" Fail");
    
  Serial.print("TopN1: ");
  Serial.print(val[5]);
  if (TN1Check)
    Serial.println(" Pass!");
  else
    Serial.println(" Fail");
    
  Serial.print("TopN2: ");
  Serial.print(val[6]);
  if (TN2Check)
    Serial.println(" Pass!");
  else
    Serial.println(" Fail");
//  if (check)
//  Serial.println(" Pass!");
//  else
//  Serial.println(" Fail:(");
}
