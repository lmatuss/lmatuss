#include <Wire.h>
#include "WaveShare_MLX90614.h"

WaveShare_MLX90614   MLX90614 = WaveShare_MLX90614();

#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200

float Temp = 0;
int Temp_map = 0;
int old_temp_map = 0;

void setup() {
  
  Serial.begin(115200);
  MLX90614.begin();  
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
 

  //Serial.print("Ambient Temp: "); Serial.print(MLX90614.readAmbientTemp()); Serial.print(" C");
  Serial.print(" \tObject Temp: "); Serial.print(MLX90614.readObjectTemp()); Serial.println(" C");
  Serial.println();
  delay(500);

        Temp = MLX90614.readObjectTemp();
          old_temp_map = Temp_map;
          Temp_map = map(Temp,18, 36, 0, stepsPerRevolution);

        // if (old_temp_map > Temp_map){
        //     while (old_temp_map > Temp_map) {
        //       digitalWrite(stepPin, HIGH );
        //       delay(100);
            // }
  

  if (Temp>=21){
    digitalWrite(dirPin, HIGH);
   // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  }
    else{
       // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
    }

  }








