#pragma once

#include "SparkFun_Toolkit.h"
#include <stdint.h>

// Available I2C addresses of the Qwiic Ultrasonic
const uint8_t kQwiicUltrasonicDefaultAddress = 0x2F;
const uint8_t kQwiicUltrasonicMinAddress = 0x08;
const uint8_t kQwiicUltrasonicMaxAddress = 0x7F;
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
    sfeTkError_t getDistace(uint16_t &distance);

    /// @brief Triggers a new measurement and reads the previous one
    /// @param distance Distance in mm
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t getTriggeredDistance(uint16_t &distance);

    /// @brief Changes the I2C address of the Qwiic Ultrasonic sensor
    /// @param address New address, must be in the range 0x20 to 0x2F
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t changeAddress(const uint8_t &address);

    /// @brief Gets the current I2C address being used by the library for the Qwiic Ultrasonic sensor
    /// @return The current I2C address, 7-bit unshifted
    uint8_t getAddress();

  protected:
    sfeTkII2C *_theBus;
};
