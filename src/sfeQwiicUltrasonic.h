#pragma once

#include "SparkFun_Toolkit.h"
#include <stdint.h>

// Available I2C addresses of the Qwiic Ultrasonic
const uint8_t kQwiicUltrasonicAddresses[] = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                                             0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F};
const uint8_t kQwiicUltrasonicNumAddresses = sizeof(kQwiicUltrasonicAddresses) / sizeof(uint8_t);
const uint8_t kQwiicUltrasonicMinAddress = kQwiicUltrasonicAddresses[0];
const uint8_t kQwiicUltrasonicMaxAddress = kQwiicUltrasonicAddresses[15];
const uint8_t kQwiicUltrasonicDefaultAddress = 0x2F;

// Register to trigger a new measuremnt and read the previous one
const uint8_t kQwiicUltrasonicRegisterTrigger = 0x01;

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

    /// @brief Gets the current I2C address of the Qwiic Ultrasonic sensor
    /// @return The current I2C address, 7-bit unshifted
    uint8_t getAddress();

  protected:
    sfeTkII2C *_theBus;
};
