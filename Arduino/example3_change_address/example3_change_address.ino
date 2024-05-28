/*SparkFun Ultrasonic Distance Sensor Example 2 - Basic Distance Sensing using I2C and Trigger Pin
* and Echo pin.
*/ 
#include <Wire.h>
const int ULTRA_ADDR = 0x2F;
const int CHANGE_ADDR = 0x04;
const int NEW_ADDR = 0x1F;
int error; 
     
void setup() {

  Wire.begin(); 

  Serial.begin(115200);  
  Serial.println("Ultrasonic Distance Sensor - Example 4 - Change Address");

  Wire.beginTransmission(ULTRA_ADDR); 
    error = Wire.endTransmission();
  if(error != 0){    
    Serial.print("Could not communicate with the sensor, check that you have the correct address, or that your sensor is connected."); 
    while(1)
      ;
  }

  Serial.println("Ready to change address.");
  Serial.println("\n\n");
  delay(1000);
}

void loop() {

  Serial.print("Changing address to: ");
  Serial.println(NEW_ADDR, HEX);
  Wire.beginTransmission(ULTRA_ADDR); 
  Wire.write(CHANGE_ADDR);
  Wire.write(NEW_ADDR << 1);
  Wire.endTransmission();
  
  delay(1000);
   
  Wire.beginTransmission((NEW_ADDR);
  error = Wire.endTransmission();             
  if(error == 0){
    Serial.print("Address changed to: ");
    Serial.println(NEW_ADDR, HEX);
    while(1)
      ;
  }
  else{
    Serial.println("Address did not change.");
    Serial.println(error);
  }
  while(1)
    ;
}
