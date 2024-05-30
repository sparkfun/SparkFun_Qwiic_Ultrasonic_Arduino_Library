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

#include "sfeQwiicUltrasonic.h"

sfeTkError_t sfeQwiicUltrasonic::begin(sfeTkII2C *theBus)
{
    // Nullptr check
    if (theBus == nullptr)
        return kSTkErrFail;

    // Check the device address
    if (theBus->address() < kQwiicUltrasonicMinAddress || theBus->address() > kQwiicUltrasonicMaxAddress)
    {
        // An older version of the firmware used 0x00 as the default address.
        // It's not really a valid address, but we need to allow it. Any other
        // address can't be used
        if (theBus->address() != 0x00)
            return kSTkErrFail;
    }

    // Set bus pointer
    _theBus = theBus;

    // Just check if the device is connected, no other setup is needed
    return isConnected();
}

sfeTkError_t sfeQwiicUltrasonic::isConnected()
{
    // Just ping the device address, there's no product ID register to check
    return _theBus->ping();
}

sfeTkError_t sfeQwiicUltrasonic::getDistance(uint16_t &distance)
{
    size_t bytesRead = 0;
    uint8_t rawData[2] = {0, 0};
    sfeTkError_t err;

    _theBus->writeByte(kUltrasonicDistanceReadCommand);
    err = _theBus->readRegisterRegion(_theBus->address(), rawData, 2, bytesRead);

    // Check whether the read was successful
    if (err != kSTkErrOk)
        return err;

    // Store raw data
    distance = (rawData[0] << 8) | rawData[1];

    // Done!
    return kSTkErrOk;
}

sfeTkError_t sfeQwiicUltrasonic::getTriggeredDistance(uint16_t &distance)
{
    size_t bytesRead = 0;
    uint8_t rawData[2] = {0, 0};

    // Attempt to read the distance
    sfeTkError_t err = _theBus->readRegisterRegion(_theBus->address(), rawData, 2, bytesRead);

    // Check whether the read was successful
    if (err != kSTkErrOk)
        return err;

    // Store raw data
    distance = (rawData[0] << 8) | rawData[1];

    // Done!
    return kSTkErrOk;
}

sfeTkError_t sfeQwiicUltrasonic::changeAddress(uint8_t &address)
{
    // Check whether the address is valid
    sfeTkError_t err;
    size_t numBytes = 2;
    address <<= 1;
    const uint8_t toWrite[2] = {kUltrasonicAddressChangeCommand, address};

    if (address < kQwiicUltrasonicMinAddress || address > kQwiicUltrasonicMaxAddress)
        return kSTkErrFail;

    // Write the new address to the device. The first bit must be set to 1
    // err = _theBus->writeRegisterByte(kUltrasonicAddressChangeCommand, (address<< 1));
    err = _theBus->writeBlock(toWrite, numBytes);

    // Check whether the write was successful
    if (err != kSTkErrOk)
        return err;

    // Update the address in the bus
    _theBus->setAddress(address);

    // Done!
    return kSTkErrOk;
}

uint8_t sfeQwiicUltrasonic::getAddress()
{
    return _theBus->address();
}
