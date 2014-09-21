// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      30
#define btness      150
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second
int point =15;
int state_p1=1;
int state_p2=1;
int buffer_1=1;
int buffer_2=1;

uint32_t Wheel(byte WheelPos) {
  WheelPos = btness - WheelPos;
  if(WheelPos < 85) {
   return pixels.Color(btness - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return pixels.Color(0, WheelPos * 3, btness - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(WheelPos * 3, btness - WheelPos * 3, 0);
  }
}

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);

  
}

void loop() {
  
///////////////////////////////////////////////////////////////////////////////////////
//                                init loop
///////////////////////////////////////////////////////////////////////////////////////  
          point = 15 ;
          state_p1=1;
          state_p2=1;
          buffer_1=1;
          buffer_2=1;
        
          while(digitalRead(2) == digitalRead(3)){
            
                  uint16_t i, j;
                
                  for(j=0; j<btness*5; j++) { // 5 cycles of all colors on wheel
                    for(i=0; i< pixels.numPixels(); i++) {
                      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
                    }
                    pixels.show();
                    delay(1);
                  }
                
          }
          while(digitalRead(2) != digitalRead(3)){
           for(int i=0;i<NUMPIXELS;i++){
              // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
              
              if(i < point){
                pixels.setPixelColor(i, pixels.Color(0,btness,0)); // Moderately bright green color.
              }else{
                pixels.setPixelColor(i, pixels.Color(btness,0,0)); // Moderately bright green color.
              }
              
              pixels.show(); // This sends the updated pixel color to the hardware.
            }
          
          }
            

          point = 15 ;
          state_p1=1;
          state_p2=1;
          buffer_1=1;
          buffer_2=1;
///////////////////////////////////////////////////////////////////////////////////////
//                                battle loop
///////////////////////////////////////////////////////////////////////////////////////
          
          while(point > 0 && point < 30){
          ///////////////////////////////////////////////////////////////////////////////////////
          //                                write led
          ///////////////////////////////////////////////////////////////////////////////////////
            for(int i=0;i<NUMPIXELS;i++){
              // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
              
              if(i < point){
                pixels.setPixelColor(i, pixels.Color(0,btness,0)); // Moderately bright green color.
              }else{
                pixels.setPixelColor(i, pixels.Color(btness,0,0)); // Moderately bright green color.
              }
              
              pixels.show(); // This sends the updated pixel color to the hardware.
            }
          ///////////////////////////////////////////////////////////////////////////////////////
          //                                read bt
          ///////////////////////////////////////////////////////////////////////////////////////
          state_p1 = digitalRead(2);
          state_p2 = digitalRead(3);
          
          if (state_p1==0 && buffer_1==1) point++;
          if (state_p2==0 && buffer_2==1) point--;
          
          buffer_1 = state_p1 ;
          buffer_2 = state_p2 ;
          }


///////////////////////////////////////////////////////////////////////////////////////
//                                fin loop
///////////////////////////////////////////////////////////////////////////////////////  

        
          
            for (int j=0;j<10;j++){
              
              for(int i=0;i<NUMPIXELS;i++){
                  // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
                  
                  if(point > 15){
                    pixels.setPixelColor(i, pixels.Color(0,btness,0)); // Moderately bright green color.
                  }else{
                    pixels.setPixelColor(i, pixels.Color(btness,0,0)); // Moderately bright green color.
                  }
                  pixels.show(); // This sends the updated pixel color to the hardware.
                }
                
                delay(80);
                  for(int i=0;i<NUMPIXELS;i++){
                    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
                    pixels.show(); // This sends the updated pixel color to the hardware.
                  }
                delay(80);
            }




}
