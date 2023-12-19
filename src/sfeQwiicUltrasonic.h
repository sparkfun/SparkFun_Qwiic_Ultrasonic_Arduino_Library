#pragma once

#include "SparkFun_Toolkit.h"
#include <stdint.h>

// Available I2C addresses of the Qwiic Ultrasonic
const uint8_t QWIIC_ULTRASONIC_ADDRESSES[] = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                                              0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F};
const uint8_t QWIIC_ULTRASONIC_NUM_ADDRESSES = sizeof(QWIIC_ULTRASONIC_ADDRESSES);
const uint8_t QWIIC_ULTRASONIC_MIN_ADDRESS = QWIIC_ULTRASONIC_ADDRESSES[0];
const uint8_t QWIIC_ULTRASONIC_MAX_ADDRESS = QWIIC_ULTRASONIC_ADDRESSES[15];
const uint8_t QWIIC_ULTRASONIC_DEFAULT_ADDRESS = 0x2F;

// Register to trigger a new measuremnt and read the previous one
const uint8_t QWIIC_ULTRASONIC_REGISTER_TRIGGER = 0x01;

class sfeQwiicUltrasonic
{
  public:
    /// @brief Default constructor
    sfeQwiicUltrasonic();

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
    sfeTkError_t triggerAndRead(uint16_t &distance);

    /// @brief Changes the I2C address of the Qwiic Ultrasonic sensor
    /// @param address New address, must be in the range 0x20 to 0x2F
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t changeAddress(uint8_t address);

  protected:
    sfeTkII2C *_theBus;
};
