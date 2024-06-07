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

// New addres is 7-bit unshifted.
uint8_t NEW_ADDR = 0x1E;
//If using an older version of the Qwiic Ultrasonic, your address range is: 0x20 - 0x2F
//uint8_t NEW_ADDR = 0x2F;


void setup()
{
    // Start serial
  Serial.begin(115200);
  Serial.println("Ultrasonic Distance Sensor - Example 4 - Change Address");

  Wire.begin();

  // This sketch wont' run until you open the serial monitor
  while(!Serial)
    ; 

  // Attempt to begin the sensor
  while (myUltrasonic.begin(deviceAddress) == false)
  {
    Serial.println("Ultrasonic sensor not connected, check your wiring and I2C address!");
    delay(2000);
  }

  Serial.println("Ready to change address.");
  delay(1000);

  Serial.print("Changing Address To: ");
  Serial.println(NEW_ADDR, HEX);


  // Call change address.....
  sfeTkError_t err =  myUltrasonic.updateAddress(NEW_ADDR);
  // If you have an older version of the Qwiic Ultrasonic, you'll need to use the following:
  //sfeTkError_t err =  myUltrasonic.changeAddress(NEW_ADDR);

  if(err)
  {
    while(1)
    {
      Serial.print("Error changing address: ");
      Serial.println(err);
      delay(1000);
    }
  }
  delay(1000);

  // I
  

  Serial.print("Load up example 1 with the new address at: ");
  Serial.println(NEW_ADDR, HEX);
  Serial.println("Freezing....");
  while(1)
    ;

}

void loop()
{
}
