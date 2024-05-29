/* SparkFun Ulrasonic Distance Sensor - Example 3 Changing the Ultrasonic's Address
 * To reset the original I2C address, ground the "RST" pad on the backside of the board.
 * by touching a wire to the pad and then to ground. The address will be reset to 0x2F.
 * 
 * Product: 
 *  *  SparkFun Qwiic Ultrasonic Distance Sensor - HC-SR04 (SEN-1XXXX)
 *  *  https://www.sparkfun.com/1XXXX
 * 
 * Written By: Elias Santistevan
 * Date: 06/2024
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 SparkFun Electronics
 */

#include "SparkFun_Qwiic_Ultrasonic_Arduino_Library.h"

// Create an ultrasonic sensor object
QwiicUltrasonic myUltrasonic;

// Here we set the device address. Note that an older version of the Qwiic
// Ultrasonic firmware used a default address of 0x00. If yours uses 0x00,
// you'll need to change the address below. It is also recommended to run
// Example 2 to change the address to the new default.
uint8_t deviceAddress = kQwiicUltrasonicDefaultAddress; // 0x2F
// uint8_t deviceAddress = 0x00;
const uint8_t NEW_ADDR = 0x1E;

void setup()
{
    // Start serial
  Serial.begin(115200);
  Serial.println("Ultrasonic Distance Sensor - Example 4 - Change Address");

  Wire.begin();

  while(!Serial)
    ; 

  // Attempt to begin the sensor
  if (myUltrasonic.begin(deviceAddress) == false)
  {
    Serial.println("Ultrasonic sensor not connected, check your wiring and I2C address!");
    while(1)
      ;
  }

  Serial.println("Ready to change address.");
  delay(1000);

}

void loop()
{
  Serial.print("Changing Address To: ");
  Serial.println(NEW_ADDR, HEX);
  // Call change address.....
  myUltrasonic.changeAddress(NEW_ADDR);
  delay(1000);
  
  Serial.println("Attempting to communicate with new address...");
  if (myUltrasonic.begin(NEW_ADDR) == false)
  {
    Serial.println("Ultrasonic sensor address did not change, ensure you picked a viable address.");
    while(1)
      ;
  }
  
  Serial.println("Address changed successfully: ");
  Serial.println(NEW_ADDR, HEX);

  while(1)
    ;
}
