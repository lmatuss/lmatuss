 //Libraries 
 #include <Wire.h>
 #include "WaveShare_MLX90614.h"
 #include <Stepper.h>

 WaveShare_MLX90614   MLX90614 = WaveShare_MLX90614();
//Zuweisen der Pins des Steppers 
 #define dirPin 2
 #define stepPin 3
 // festelgen der Stufen und der Geschwindigkeit, mit der der Stepper sich bewegen soll 
 #define stepsPerRevolution 18
 #define speeed 2500

 float Temp = 0;
 int Temp_map = 0;
 int old_temp_map = 0;

 void setup() {

   Serial.begin(115200);
   MLX90614.begin();  
   pinMode(stepPin, OUTPUT);
   pinMode(dirPin, OUTPUT);
          
          
          //einmalige Positionseinstellung --> Verspannung des Exponates
          digitalWrite(dirPin, HIGH);
          for (int i = 0; i < 10*stepsPerRevolution; i++) {
             digitalWrite(stepPin, HIGH);
             delayMicroseconds(speeed);
             digitalWrite(stepPin, LOW);
             delayMicroseconds(speeed);
           }
          
             
 }
 void loop() {

// Kontrolle, ob der Infarotsensor richtig misst 
   Serial.print(" \tObject Temp: "); Serial.print(MLX90614.readObjectTemp()); Serial.println(" C");
   Serial.println();
   delay(500);

//Übersetzung der gemessenen Temperatur in einen Wert, welcher auf die Steps des Motors gemapt wird
   Temp = MLX90614.readObjectTemp();
   old_temp_map = int(Temp_map);
   Temp_map = map(Temp*10,180, 360, 0, stepsPerRevolution);

// Vergeich der aktuellen Temperatur mit der vorherig gemessenen --> aktueller < alte = Exponat verspannt sich 
       if (old_temp_map > Temp_map){
         while (old_temp_map > Temp_map){
           // Festlegen in welche Richtung der Motor sich dreht
         digitalWrite(dirPin, HIGH);   
           for (int i = 0; i < stepsPerRevolution; i++) {
            // Stepper dreht sich 
             digitalWrite(stepPin, HIGH);
             delayMicroseconds(speeed);
             digitalWrite(stepPin, LOW);
             delayMicroseconds(speeed);
           }
               old_temp_map--;
   }
       }

// Vergeich der aktuellen Temperatur mit der vorherig gemessenen --> aktuelle > alte = Exponat entspannt sich 
       else if (old_temp_map < Temp_map){
         while (old_temp_map < Temp_map) {
           // Festlegen in welche Richtung der Motor sich dreht
         digitalWrite(dirPin, LOW);   
           for (int i = 0; i < stepsPerRevolution; i++) {
             // Stepper dreht sich 
             digitalWrite(stepPin, HIGH);
             delayMicroseconds(speeed);
             digitalWrite(stepPin, LOW);
             delayMicroseconds(speeed);
         }
         old_temp_map++;
         }
       }

       // Gibt es keine Tempraturveränderungen, bewegt sich der Motor nicht 
       else {
         digitalWrite(stepPin, LOW);
       }

    }




