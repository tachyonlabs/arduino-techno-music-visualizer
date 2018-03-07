#include <FastLED.h>

#define DATA_PIN     6
#define NUM_LEDS    20
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

//Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1 

// I'm seeing best results using band 4 to isolate the drumbeats
#define DRUM_BAND 4

// Depending on the music you're playing and the volume you have it set to, you may need to tweak either the 
// volume or this level to respond to all the drumbeats but not to other elements of the music
#define DRUM_VOLUME_THRESHOLD 170

//Define spectrum variables
int Frequencies_One[7];
int Frequencies_Two[7]; 
int hue = 0;

void setup() {
  delay( 3000 ); // power-up safety delay

  //Set spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);  
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);

  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  turnOffAllLeds();
}

void loop() {
  listenAndFade();
}

void turnOffAllLeds() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void listenAndFade() {
  // we're fading all the time, but only going to 100% brightness when there's a beat
  Read_Frequencies();
  fadeToBlackBy(leds, NUM_LEDS, 1);
  FastLED.show();
}

/*************Pull frquencies from Spectrum Shield****************/
void Read_Frequencies() {
  //Read frequencies for each band
  for (int freq_amp = 0; freq_amp < 7; freq_amp++) {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    Frequencies_Two[freq_amp] = analogRead(DC_Two); 
    if (freq_amp == DRUM_BAND && (Frequencies_One[DRUM_BAND] > DRUM_VOLUME_THRESHOLD || Frequencies_Two[DRUM_BAND] > DRUM_VOLUME_THRESHOLD)) {
      // we're fading all the time, but only going to 100% brightness when there's a beat
      fill_solid(leds, NUM_LEDS, CHSV(hue, 255, 255));
      // might as well have some color variation
      hue = (hue + 1) % 256;
    }
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
}

