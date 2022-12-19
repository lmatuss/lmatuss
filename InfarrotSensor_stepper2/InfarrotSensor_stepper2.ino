#include <Wire.h>
#include "WaveShare_MLX90614.h"
//Libraries:
#include <AccelStepper.h>

#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1
#define stepsPerRevolution 200
    
  

//Temp Declarations:
  float Temp = 0;
  int Temp_map=0;
  int old_temp_map=0;

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
WaveShare_MLX90614   MLX90614 = WaveShare_MLX90614();



void setup() {
  
  Serial.begin(115200);
  MLX90614.begin(); 

  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(200);
  stepper.moveTo(500);
  
}

void loop() {
 

  //Serial.print("Ambient Temp: "); Serial.print(MLX90614.readAmbientTemp()); Serial.print(" C");
  Serial.print(" \tObject Temp: "); Serial.print(MLX90614.readObjectTemp()); Serial.println(" C");
  Serial.println();
  delay(500);

  Temp = MLX90614.readObjectTemp();
  // old_temp_map = Temp_map;
  // Temp_map = map(Temp*10,180, 360, 0, stepsPerRevolution );  

  // Set the position to 0:
  //stepper.setCurrentPosition(0);

      if (Temp>=22){
         digitalWrite(dirPin, HIGH);
       // Spin the stepper motor 1 revolution slowly:
      for (int i = 0; i < stepsPerRevolution; i++) {
        // These four lines result in 1 step:
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);
        }
      }

      //stepper.setCurrentPosition(100);

  else {
  digitalWrite(dirPin, LOW);
  stepper.moveTo(-stepper.currentPosition());

  
  }


  }
  





