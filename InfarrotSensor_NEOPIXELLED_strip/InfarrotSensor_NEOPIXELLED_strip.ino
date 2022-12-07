#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "WaveShare_MLX90614.h"

WaveShare_MLX90614   MLX90614 = WaveShare_MLX90614();



#define PIN        9
#define NUMPIXELS 72 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50 

void setup() {

  pixels.begin(); 
  MLX90614.begin(); 
  
}

void loop() {

    pixels.clear(); // Set all pixel colors to 'off'

  
  //Serial.print("Ambient Temp: "); Serial.print(MLX90614.readAmbientTemp()); Serial.print(" C");
  Serial.print(" \tObject Temp: "); Serial.print(MLX90614.readObjectTemp()); Serial.println(" C");
  Serial.println();
  delay(500);

  if(MLX90614.readObjectTemp()>=22.00){
    for(int i=0; i<NUMPIXELS; i++) { 

    pixels.setPixelColor(i, pixels.Color(25, 10, 0)); // Rot, Grün, Blau

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop

    
  
  
    }}
     if(MLX90614.readObjectTemp()<22.00){
       for(int i=0; i<NUMPIXELS; i++) { 

     
    pixels.show(pixels.Color(0, 0, 0)); // Rot, Grün, Blau

  
  }
  }}