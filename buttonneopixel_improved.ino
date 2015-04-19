/*
  Simple BlinkyStrip control
   
  This sketch allows serial control over a BlinkyStrip.
  To set any pixel in the strip, send the following serial string:
   
  Cr,g,b
   
  r, g, and b are ASCII numbers for the red, green, and blue brightness
  levels, from 0 to 255.
   
  This will probably work for any string of NeoPixels from Adafruit as well.
   
  Uses Adafruit's NeoPixel library: https://github.com/adafruit/Adafruit_NeoPixel
   
  created 4 Dec 2014
  by Tom Igoe
 
*/
#include <Adafruit_NeoPixel.h>
#include <math.h>       /* ceil */
 
#define PIN 6
#define NUM_LEDS 144
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
int pixel = 0;            // pixel number that you're changing
unsigned int time = 60000;
int red = 0;              // red value 
int green = 34;           // green value
int blue = 12;            // blue value
int space = 1;
int go = 0;
unsigned int lastt = 60000;
unsigned int lowestt = 60000;
int lowestp;
int serinput;
int s;
int pixelfade;
int brghtnss = 100;
int scbrghtnss;
int lastp;
int ovrwrt;
int scpx[] = {0,16,17,36,37,56,57,76,77,96,97,120};
unsigned long start, elapsed;
int clr[6][3] = {  
 {102, 0, 102} ,   // purple
 {0, 0, 255} ,   // blue
 {0, 255, 0} , //green
 {255, 192, 0} ,   //yellow
 {255, 96, 0} ,   // orange
 {255, 0, 0}  // red
};
int clrrw;
int incomingByte = 0;
 
void setup() {
  Serial.begin(9600);     // initialize serial communication
  Serial.setTimeout(10);  // set serial timeout
  strip.begin();          // initialize pixel strip
  strip.show();           // Initialize all pixels to 'off'
  scbrghtnss = round(brghtnss/10);
}
 
void loop() {
  // listen for serial:
  if (serinput !=0) { tone(3,10000,5); }
  
  //while (1) {
    serinput = Serial.parseInt();

  //}
  //while(time>=0){
  if (serinput !=0){
      lastt=time;
      if (lastt<lowestt) {
        lowestt=lastt;
        lowestp=floor((60000-lowestt)*0.002);
        
        Serial.print("New Lowest Value:");
        Serial.println(lowestp);
      }
      lastp=pixel-1;
      startover();
      time=serinput*10;
      start=millis();
      serinput=10001;
      go=1;
      Serial.println("Reset");
     
  }
  
    //delay(100);
    elapsed=millis()-start;
    //Serial.println(elapsed);
    time=round(60000-elapsed);
    //Serial.println(time);
    
    pixel = floor((60000-time)*0.002);
    //Serial.println(pixel);
    pixelfade = (((60000-time)*0.002)-pixel)*brghtnss;
    //Serial.println(pixelfade);
    
    if  (time >=52000) {
      clrrw=0;
    } else if (time >=42000) {
      clrrw=1;
    } else if (time >=32000) {
      clrrw=2;
    } else if (time >=22000) {
      clrrw=3;
    } else if (time >=12000) {
      clrrw=4;
    } else if (time >=100) {
      clrrw=5;
    }
    lstdrpdwn();
    if (go!=0){
      for (int i=0; i < pixel; i++) {
        strip.setPixelColor(i, fdbrghtnss(clr[clrrw][0],clr[clrrw][1],clr[clrrw][2],brghtnss));// set the color for this pixel
      }
      strip.setPixelColor(pixel, fdbrghtnss(clr[clrrw][0],clr[clrrw][1],clr[clrrw][2],pixelfade));
      //setscale();
      strip.show();  // refresh the strip
    }    
    delay(40);
  //}
}

void startover() {
  for (int i=0; i < NUM_LEDS; i++) {
     strip.setPixelColor(i, 0, 0, 0);// set the color for this pixel
  }
  strip.setPixelColor(lowestp, fdbrghtnss(255,255,255,scbrghtnss));
  setscale();
  strip.show();
}

void setscale() {
  strip.setPixelColor(scpx[0], fdbrghtnss(clr[0][0],clr[0][1],clr[0][2],scbrghtnss));// set the color for this pixel
  strip.setPixelColor(scpx[1], fdbrghtnss(clr[0][0],clr[0][1],clr[0][2],scbrghtnss));// set the color for this pixel
  strip.setPixelColor(scpx[2], fdbrghtnss(clr[1][0],clr[1][1],clr[1][2],scbrghtnss));// set the color for this pixel
  strip.setPixelColor(scpx[3], fdbrghtnss(clr[1][0],clr[1][1],clr[1][2],scbrghtnss));// set the color for this pixel
  strip.setPixelColor(scpx[4], fdbrghtnss(clr[2][0],clr[2][1],clr[2][2],scbrghtnss));// set the color for this pixel
  strip.setPixelColor(scpx[5], fdbrghtnss(clr[2][0],clr[2][1],clr[2][2],scbrghtnss));// set the color for this pixel
  strip.setPixelColor(scpx[6], fdbrghtnss(clr[3][0],clr[3][1],clr[3][2],scbrghtnss));// set the color for this pixel
  strip.setPixelColor(scpx[7], fdbrghtnss(clr[3][0],clr[3][1],clr[3][2],scbrghtnss));// set the color for this pixel
  strip.setPixelColor(scpx[8], fdbrghtnss(clr[4][0],clr[4][1],clr[4][2],scbrghtnss));// set the color for this pixel
  strip.setPixelColor(scpx[9], fdbrghtnss(clr[4][0],clr[4][1],clr[4][2],scbrghtnss));// set the color for this pixel
  strip.setPixelColor(scpx[10], fdbrghtnss(clr[5][0],clr[5][1],clr[5][2],scbrghtnss));// set the color for this pixel
  strip.setPixelColor(scpx[11], fdbrghtnss(clr[5][0],clr[5][1],clr[5][2],scbrghtnss));// set the color for this pixel
}


uint32_t fdbrghtnss(int rd, int grn, int bl, int prcnt) {
  int nrd=round((rd*prcnt)/100);
  int ngrn=round((grn*prcnt)/100);
  int nbl=round((bl*prcnt)/100);
  uint32_t fdbrghtnss = strip.Color(nrd, ngrn, nbl);
}


void lstdrpdwn() {
  ovrwrt=1;
  lastp = lastp-1;
  if (lastp > pixel) {
    if (ovrwrt=1) {
      strip.setPixelColor(lastp+1, strip.Color(0,0,0));
      strip.setPixelColor(lastp, fdbrghtnss(255,255,255,scbrghtnss));
      setscale();
    }
    
  }
}
