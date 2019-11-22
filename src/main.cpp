#include <Arduino.h>
#include "FastLED.h"

FASTLED_USING_NAMESPACE

#define DATA_PIN    5

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    30

#define BRIGHTNESS          180
#define FRAMES_PER_SECOND  100

void testled();

int delta=0;
bool sens=true;
int phase=1;

CRGB leds[NUM_LEDS];

DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
  0,   9,    4,  140,//black
128,   255,  0,  0,   //red
224,   255,255,  0,   //bright yellow
255,   255,255,255 }; //full white

CRGBPalette16 myPal = heatmap_gp;


const  PROGMEM char scenario[]="{ "
	"\"SceneElements\": [{\"name\":\"Sun\",\"type\":\"sun\"},{\"name\":\"Sky\",\"type\":\"sky\"}], "

	"\"ScenePhases\":[{\"name\":\"appearing\",\"duration\":6000,\"order\":1, "
				 "\"SceneElements\": [{\"name\":\"Sun\",\"animation\":\"fullday\",\"zorder\":1}, "
								   "{\"name\":\"Sky\",\"animation\":\"fullday\",\"zorder\":2}]	 "
				 "}, "
				 "{\"name\":\"sunrise\",\"duration\":6000,\"order\":2, "
				 "\"SceneElements\": [{\"name\":\"Sun\",\"animation\":\"sunrise\",\"zorder\":1}, "
								  "{\"name\":\"Sky\",\"animation\":\"sunrise\",\"zorder\":2}]	 "
				 "}, "
				 "{\"name\":\"night\",\"duration\":6000,\"order\":3, "
				 "\"SceneElements\": [{\"name\":\"Sky\",\"animation\":\"night\",\"zorder\":1}]	 "
				 "} "
				"] "
  "}";


void setup() {
  Serial.begin(9600);
  
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  EVERY_N_SECONDS( 7 ) { testled(); } // change patterns periodically
}


void testled(){
  /*
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = CRGB::White;
  } 
  */
 /*
 Serial.print(r);
 Serial.print("\r\n");
 fill_solid( &(leds[0]), NUM_LEDS, CRGB( r, 0, 0) ); 
 if (sens) {
    r++;
    if (r>=255) sens=false;
 }
 else {
    r--;
    if (r<=0) sens=true;
 }
 */

  /*
  for( int i = 0; i < NUM_LEDS; i++) {
    int index= ( i*255/NUM_LEDS) - delta;
    if (index<=0) index=0;
    Serial.print(index);
    Serial.print("\r\n");
    leds[i] = ColorFromPalette( myPal, index);
    
  }
  */
 if (phase==1){
    int index;
    for( int i = 0; i <= 15; i++) {
      index= ( i*255/15) - delta;
      if (index<=0) index=0;
      Serial.print(index);
      Serial.print("\r\n");
      leds[i] = ColorFromPalette( myPal, index);
      leds[29-i] = leds[i];
    }
    delta++;
    if(delta>=255) {
      
      phase++;
      
    }

  
 }
 if(phase==2){
   if (delta==255) delta=BRIGHTNESS;
   FastLED.setBrightness(delta);
   delta--;
   if(delta<=0) {
      delta=0;
      phase=1;
      FastLED.setBrightness(BRIGHTNESS);
    }
 }

  /*
  for( int i = 15; i <= 30; i++) {
    int index= ( i*255/15) - delta;
    if (index<=0) index=0;
    Serial.print(index);
    Serial.print("\r\n");
    leds[30-(15-i)] = ColorFromPalette( myPal, index);
    
  }
  */
  

  




}
