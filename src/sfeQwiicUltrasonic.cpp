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
#include "sfeTk/sfeTkError.h"

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
    size_t bytesRead;
    size_t numBytes = 2;
    uint8_t rawData[2] = {};

    // Get the distance
    sfeTkError_t err = _theBus->readBlock(kUltrasonicDistanceReadCommand, rawData, numBytes, bytesRead);

    // Check whether the read was successful
    if (err != kSTkErrOk)
        return err;

    // Store raw data
    distance = (rawData[0] << 8) | rawData[1];

    // Done!
    return kSTkErrOk;
}

sfeTkError_t sfeQwiicUltrasonic::changeAddress(const uint8_t &address)
{
    // Check whether the address is valid
    if (address < kQwiicUltrasonicMinAddress || address > kQwiicUltrasonicMaxAddress)
        return kSTkErrFail;

    // Write the new address to the device. The first bit must be set to 1
    sfeTkError_t err = _theBus->writeByte(address | 0x80);

    // Check whether the write was successful
    if (err != kSTkErrOk)
        return err;

    // Update the address in the bus
    _theBus->setAddress(address);

    // Done!
    return kSTkErrOk;
}

sfeTkError_t sfeQwiicUltrasonic::updateAddress(uint8_t &address)
{
    // Check whether the address is valid
    sfeTkError_t err;
    size_t numBytes = 2;
    // We want to shift the address left before we send it. 
    
    address <<= 1;
    const uint8_t toWrite[2] = {kUltrasonicAddressChangeCommand, address};

    if (address < kQwiicI2CAddressMin|| address > kQwiicI2CAddressMax)
        return kSTkErrFail;

    // Write the new address to the device. 
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
