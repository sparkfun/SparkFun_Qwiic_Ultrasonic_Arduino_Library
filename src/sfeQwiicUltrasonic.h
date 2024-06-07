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

#include "SparkFun_Toolkit.h"
#include <stdint.h>

// Available I2C addresses of the Qwiic Ultrasonic
const uint8_t kQwiicUltrasonicDefaultAddress = 0x2F;
// These addresses are the min and max (respectively) of valid I2C addresses that can
// be used for the newest revision of the Qwiic Ultrasonic sensor.
const uint8_t kQwiicI2CAddressMin = 0x08;
const uint8_t kQwiicI2CAddressMax = 0x7F;
// Available I2C addresses of the Qwiic Ultrasonic
const uint8_t kQwiicUltrasonicAddresses[] = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                                             0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F};
const uint8_t kQwiicUltrasonicNumAddresses = sizeof(kQwiicUltrasonicAddresses) / sizeof(uint8_t);
const uint8_t kQwiicUltrasonicMinAddress = kQwiicUltrasonicAddresses[0];
const uint8_t kQwiicUltrasonicMaxAddress = kQwiicUltrasonicAddresses[15];;
// I2C commands
const uint8_t kUltrasonicDistanceReadCommand = 0x01;
const uint8_t kUltrasonicAddressChangeCommand = 0x04;

class sfeQwiicUltrasonic
{
  public:
    /// @brief Default constructor
    sfeQwiicUltrasonic() : _theBus(nullptr)
    {
    }

    /// @brief Begins the Qwiic Ultrasonic sensor
    /// @param theBus I2C bus to use for communication
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t begin(sfeTkII2C *theBus = nullptr);

    /// @brief Checks if the Qwiic Ultrasonic sensor is connected
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t isConnected();

    /// @brief Triggers a new measurement and reads the previous one
    /// @param distance Distance in mm
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t getDistance(uint16_t &distance);

    /// @brief Changes the I2C address of older Qwiic Ultrasonic sensors.
    /// @param address New address, must be in the range 0x20 to 0x2F
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t changeAddress(const uint8_t &address);

    /// @brief Changes the I2C address of the latest revision of the Qwiic Ultrasonic sensor.
    /// @param address New address, must be in the range 0x20 to 0x2F
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t updateAddress(uint8_t &address);

    /// @brief Gets the current I2C address being used by the library for the Qwiic Ultrasonic sensor
    /// @return The current I2C address, 7-bit unshifted
    uint8_t getAddress();

  protected:
    sfeTkII2C *_theBus;
};
