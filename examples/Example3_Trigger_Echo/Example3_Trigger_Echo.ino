/* SparkFun Ulrasonic Distance Sensor - Example 3 - Distance using Trigger and Echo Pins
 * 
 * Product: 
 *  *  SparkFun Qwiic Ultrasonic Distance Sensor - HC-SR04 (SEN-24805)
 *  *  https://www.sparkfun.com/products/24805
 * 
 * Written By: Elias Santistevan and Xavior Pautin
 * Date: 09/2024
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 SparkFun Electronics
 */
// Using the echo and trigger breakout pins does not require a QWIIC connector I2C connection
// Adjust these pins to your setup
const int triggerPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 8; // Echo Pin of Ultrasonic Sensor

// Used for distance calculation
float distance = 0.0;
float duration = 0.0;
const float speedOfSound = 0.343; // Speed of sound in mm/us

void setup() {
  Serial.begin(115200);
  Serial.println("Ultrasonic Distance Sensor - Example 3 Distance using Trigger and Echo Pins");

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Required pulse to trigger the ultrasonic sensor
  // delayMicroseconds() must be greater than 10us, but less than 200us
  // 10 microseconds is the minimum pulse width listed by the manufacturer
  // 200 microseconds is the approximate delay between the rise of the trigger pulse
  // and fall of the echo pulse
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(50);
  digitalWrite(triggerPin, LOW);

  // pulseIn() set LOW because the echo pin of the sensor outputs a negative pulse from HIGH to LOW
  // pulseIn() duration is in microseconds
  duration = pulseIn(echoPin, LOW);

  // Divide by two because we only want the time the wave traveled to the object, 
  // not to the object and back.
  distance = (duration * speedOfSound) / 2;

  // Print measurement
  Serial.print("Distance (mm): ");
  Serial.println(distance, 1); // Print to 1 decimal place

  // Serial.print("Distance (cm): ");
  // Serial.println((distance / 10.0), 2); // Print to 2 decimal places

  //Serial.print("Distace (in): ");
  //Serial.println((distance / 25.4), 2); // Print to 2 decimal places

  delay(500);
}
