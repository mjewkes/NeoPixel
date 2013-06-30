#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_RGB Pixels are wired for RGB bitstream
// NEO_GRB Pixels are wired for GRB bitstream
// NEO_KHZ400 400 KHz bitstream (e.g. FLORA pixels)
// NEO_KHZ800 800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(720, 10, NEO_GRB + NEO_KHZ800);
const int waveNums = 10;
uint16_t wavelets[] = {0, 80, 160, 240, 320, 400,480,560,620,700};
int glowdir =1;
int intensity=0;
void glow(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, intensity, 0,0);
  }
  intensity+=glowdir;
  if (intensity>= 50){
    glowdir=-1;
  }
  if (intensity<=0){
    glowdir=1;
  }
  strip.show();
  delay(5);
}
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
 // glow();
  waves();
  //colorWipe(strip.Color(200,50,0),20);
//  colorWipe(strip.Color(255,0,0),20);
}
const int waveSize=20;
const int waveHalf = 10;
int val;
void waves(){
  static int dir = 1;
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 5,10);
  }
  for (int j=0;j<waveNums;j++){
    wavelets[j]++;
    if (wavelets[j]>strip.numPixels()){
       wavelets[j] = 0;
    }
    wave (wavelets[j]);
  }
      strip.setPixelColor(random(0,strip.numPixels()), 255,255,255);
      strip.setPixelColor(random(0,strip.numPixels()), 255,255,255);
      strip.setPixelColor(random(0,strip.numPixels()), 255,255,255);
      strip.setPixelColor(random(0,strip.numPixels()), 255,255,255);
  //val = analogRead(0);
  strip.setPixelColor(2, val,val,val);
 // pulse();
  strip.show();
  delay(50);

}
int isPulsing = -1;
int pulseTime = 0;
void pulse(){
  if (isPulsing==-1){
    //if (random(0,50==0)){
      isPulsing =random(0,strip.numPixels());
   // }
  }else{
    int i=isPulsing;
    for( ; i<isPulsing+30; i++) {
      if (i>=strip.numPixels()) break;
      strip.setPixelColor(i, 0, 125,0);
    }
  }
  pulseTime++;
  if (pulseTime>50){
     pulseTime=0;
    isPulsing=-1;
  }
}
void wave(uint16_t pos){
  const int waveStrength=2;
  int i=pos;
  for( ; i<pos+waveHalf; i++) {
    int offset = (i-pos)*waveStrength;
    if (i>=strip.numPixels()) return;
        strip.setPixelColor(i, 0, 10+offset,5+offset);
  }
  int peak = (i-pos)*waveStrength;
  
  for(; i<pos+waveSize; i++) {
    int offset = (pos+waveHalf-i)*waveStrength;
    if (i>=strip.numPixels()) return;
        strip.setPixelColor(i, 0,10+peak-offset,5+peak-offset);
  }

}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
