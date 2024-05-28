/*SparkFun Ultrasonic Distance Sensor - Qwiic example 1 - Basic Distance Sensing using I2C
*
*/ 
#include <Wire.h>
const int ULTRA_ADDR = 0x2F;
const int BEGIN_MEASURE = 0x01;
int distance, distance_H, distance_L=0;
     
void setup() {

  Wire.begin(); 

  Serial.begin(115200);  
  Serial.println("Ultrasonic Distance Sensor - Example 1 Basic Distance Sensing.");

  Wire.beginTransmission(ULTRA_ADDR); 
    int error = Wire.endTransmission();
  if(error != 0){    
    Serial.print("Could not communicate with the sensor, check that you have the correct address, or that your sensor is connected."); 
    while(1)
      ;
  }

  Serial.println("Ready to check distance.");
  Serial.println("\n\n");
  delay(1000);
}

void loop() {

  Wire.beginTransmission(ULTRA_ADDR);
  Wire.write(BEGIN_MEASURE);              
  Wire.endTransmission();    
  delay(20);

  Wire.requestFrom(ULTRA_ADDR, 2);
  delay(20);

  while (Wire.available()) { 
    distance_H = Wire.read(); 
    distance_L = Wire.read();  
    distance = distance_H << 8;
    distance = distance|distance_L; 

    Serial.print("Distance: ");
    Serial.print(distance);         
    Serial.println("mm"); 

    //Serial.print("Distance: ");
    //Serial.print(distance / 10.0);         
    //Serial.println("cm", 2); 

    //Serial.print("Distance: ");
    //Serial.print(distance / 25.4);         
    //Serial.println("in", 2); 
  }

  Serial.println("\n");
  delay(500);
}
