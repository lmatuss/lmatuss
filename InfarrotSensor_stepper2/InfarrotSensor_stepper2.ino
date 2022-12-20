#include <Wire.h>
#include "WaveShare_MLX90614.h"
#include <Stepper.h>


WaveShare_MLX90614   MLX90614 = WaveShare_MLX90614();

#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 18
#define speeed 1000

float Temp = 0;
int Temp_map=0;
int old_temp_map=0;


void setup() {
  
  Serial.begin(115200);
  MLX90614.begin();  
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  //Serial.print(" \tObject Temp: "); Serial.print(MLX90614.readObjectTemp()); Serial.println(" C");
  //Serial.println();
  //delay(500);

  Temp = MLX90614.readObjectTemp();
  old_temp_map = int(Temp_map);
  Temp_map = map(Temp*10,180, 360, 0, stepsPerRevolution);
       
      if (old_temp_map > Temp_map){
        while (old_temp_map > Temp_map){
        digitalWrite(dirPin, HIGH);   //set direction
        // Spin the stepper motor 1 revolution slowly:
          for (int i = 0; i < stepsPerRevolution; i++) {
            // These four lines result in 1 step:
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(speeed);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(speeed);
          }
              old_temp_map--;
  }
      }
      else if (old_temp_map < Temp_map){
        while (old_temp_map < Temp_map) {

        
         digitalWrite(dirPin, LOW);   //set direction
        // Spin the stepper motor 1 revolution slowly:
          for (int i = 0; i < stepsPerRevolution; i++) {
            // These four lines result in 1 step:
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(speeed);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(speeed);

      }
            old_temp_map++;
        }
      }
      else {
        digitalWrite(dirPin, LOW);
        digitalWrite(stepPin, LOW);

      }



}
  
