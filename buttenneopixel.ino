/*
  Modified BlinkyStrip 
  by Tom Igoe
  Uses Adafruit's NeoPixel library: https://github.com/adafruit/Adafruit_NeoPixel

*/
#include <Adafruit_NeoPixel.h>
#include <math.h>       /* ceil */
 
#define PIN 6
#define NUM_LEDS 144
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
int pixel = 0;            // pixel number that you're changing
int time = 0;
int red = 0;              // red value 
int green = 34;           // green value
int blue = 12;            // blue value
int space = 1;
int seconds = 600;
int s;
uint32_t clr = strip.Color(0,0,0);
uint32_t clr1 = strip.Color(102, 0, 102); // purple
uint32_t clr2 = strip.Color(0, 0, 255); // blue
uint32_t clr3 = strip.Color(0, 255, 0); //green
uint32_t clr4 = strip.Color(255, 192, 0); //yellow
uint32_t clr5 = strip.Color(255, 96, 0); // orange
uint32_t clr6 = strip.Color(255, 0, 0); // red

int incomingByte = 0;
 
void setup() {
  Serial.begin(9600);     // initialize serial communication
  Serial.setTimeout(10);  // set serial timeout
  strip.begin();          // initialize pixel strip
  strip.show();           // Initialize all pixels to 'off'
}
 
void loop() {
  // listen for serial:
  if (seconds !=0) { tone(3,10000,5); }
  
  while (1) {
    seconds = Serial.parseInt();
    if (seconds !=0) {
      s = seconds;
      break;
    }
  }
  time = s;
//  if (Serial.available() >= 2) {
//    if (Serial.read() == 'T') {    // string should start with C
//      time = Serial.parseInt();   // then an ASCII number for pixel number
//      Serial.print("I received: ");
//      Serial.println(time);
//    }
//  }
//  for (int j=1; j < 600; j++) {
//    time=600-j;
    if  (time >=520) {
      clr=clr1;
      space=0;
    } else if (time >=420) {
      clr=clr2;
      space=0;
    } else if (time >=320) {
      clr=clr3;
      space=0;
    } else if (time >=220) {
      clr=clr4;
      space=0;
    } else if (time >=120) {
      clr=clr5;
      space=0;
    } else if (time >=1) {
      clr=clr6;
      space=0;
    }
    pixel = round((600-time)*0.2)+space;
    for (int i=0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, 0, 0, 0);// set the color for this pixel
    }
    for (int i=0; i < pixel; i++) {
      strip.setPixelColor(i, clr);// set the color for this pixel
    }
    strip.setPixelColor(0, clr1);// set the color for this pixel
    strip.setPixelColor(16, clr1);// set the color for this pixel
    strip.setPixelColor(17, clr2);// set the color for this pixel
    strip.setPixelColor(36, clr2);// set the color for this pixel
    strip.setPixelColor(37, clr3);// set the color for this pixel
    strip.setPixelColor(56, clr3);// set the color for this pixel
    strip.setPixelColor(57, clr4);// set the color for this pixel
    strip.setPixelColor(76, clr4);// set the color for this pixel
    strip.setPixelColor(77, clr5);// set the color for this pixel
    strip.setPixelColor(96, clr5);// set the color for this pixel
    strip.setPixelColor(97, clr6);// set the color for this pixel
    strip.setPixelColor(120, clr6);// set the color for this pixel
    
    delay(50);
  strip.setBrightness(32);
  strip.show();                                // refresh the strip
//}
}
