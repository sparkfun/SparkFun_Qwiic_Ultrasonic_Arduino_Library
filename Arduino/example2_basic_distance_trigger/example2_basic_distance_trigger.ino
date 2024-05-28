/*SparkFun Ultrasonic Distance Sensor Example 2 - Basic Distance Sensing using I2C and Trigger Pin
* and Echo pin.
*/ 

#include <Wire.h>
const int ULTRA_ADDR = 0x2F;
const int BEGIN_MEASURE = 0x01;
int distanceRequested = 0;  
int distance, distance_H, distance_L=0;
int triggerPin = 7; // Trigger Pin of Ultrasonic Sensor
int echoPin = 8; // Echo Pin of Ultrasonic Sensor
     
void setup() {

  Wire.begin(); 

  Serial.begin(115200);  
  Serial.println("Ultrasonic Distance Sensor - Example 1 Basic Distance Sensing.");

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

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

  if(distanceRequested == 0)
  {    
    digitalWrite(triggerPin, HIGH);
    delay(5);
    digitalWrite(triggerPin, LOW);
    distanceRequested = 1;
  }

  if (digitalRead(echoPin) == LOW) {
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
      Serial.println("\n");
    }
    distanceRequested = 0;
  }
  delay(500);
}
