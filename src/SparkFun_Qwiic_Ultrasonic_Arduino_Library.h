/* SparkFun Ulrasonic Distance Sensor 
 * 
 * Product: 
 *  *  SparkFun Qwiic Ultrasonic Distance Sensor - HC-SR04 (SEN-1XXXX)
 *  *  https://www.sparkfun.com/1XXXX
 * 
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 SparkFun Electronics
 */

#pragma once

#include "Arduino.h"
#include "sfeQwiicUltrasonic.h"
#include <Wire.h>

class QwiicUltrasonic : public sfeQwiicUltrasonic
{
  public:
    /// @brief Begins the Qwiic Ultrasonic sensor
    /// @param address I2C device address to use for the sensor
    /// @param wirePort Wire port to use for I2C communication
    /// @return True if successful, false otherwise
    bool begin(uint8_t address = kQwiicUltrasonicDefaultAddress, TwoWire &wirePort = Wire)
    {
        // Setup Arudino I2C bus
        _theI2CBus.init(wirePort, address);

        // Begin the sensor
        return sfeQwiicUltrasonic::begin(&_theI2CBus) == kSTkErrOk;
    }

    /// @brief Checks if the Qwiic Ultrasonic sensor is connected
    /// @return True if the sensor is connected, false otherwise
    bool isConnected()
    {
        return sfeQwiicUltrasonic::isConnected() == kSTkErrOk;
    }

  private:
    sfeTkArdI2C _theI2CBus;
};
