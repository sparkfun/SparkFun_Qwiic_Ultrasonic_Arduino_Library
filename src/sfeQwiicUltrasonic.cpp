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
    if (_fwVersion == kQwiicUltrasonicFWOld)
    {
        if (theBus->address() < kQwiicUltrasonicMinAddress || theBus->address() > kQwiicUltrasonicMaxAddress)
        {
            // An older version of the firmware used 0x00 as the default address.
            // It's not really a valid address, but we need to allow it. Any other
            // address can't be used
            if (theBus->address() != 0x00)
                return kSTkErrFail;
        }
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

sfeTkError_t sfeQwiicUltrasonic::triggerAndRead(uint16_t &distance)
{
    size_t bytesRead;
    size_t numBytes = 2;
    uint8_t rawData[2] = {};

    // Get the distance
    sfeTkError_t err = _theBus->readRegisterRegion(kUltrasonicDistanceReadCommand, rawData, numBytes, bytesRead);

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

    if (_fwVersion == kQwiicUltrasonicFWOld)
    {
        // Old firmware only supports a limited range of addresses.
        if (address < kQwiicUltrasonicMinAddress || address > kQwiicUltrasonicMaxAddress)
            return kSTkErrFail;

        // Write the new address to the device. The first bit must be set to 1
        err = _theBus->writeByte(address | 0x80);
    }
    else if (_fwVersion == kQwiicUltrasonicFWLatest)
    {
        size_t numBytes = 2;
        // Latest firmware versions supports all of the available I2C addresses.
        if (address < kQwiicUltrasonicI2CAddressMin || address > kQwiicUltrasonicI2CAddressMax)
            return kSTkErrFail;

        // We want to shift the address left before we send it.
        uint8_t tempAddress = address << 1;
        const uint8_t toWrite[2] = {kUltrasonicAddressChangeCommand, tempAddress};

        // Write the new address to the device
        err = _theBus->writeRegion(toWrite, numBytes);
    }
    else
    {
        // There was some error setting the version in the constructor
        // return an error.
        return kSTkErrFail;
    }

    _theBus->setAddress(address);
    // Check whether the write was successful
    if (err != kSTkErrOk)
        return err;

    // Done!
    return kSTkErrOk;
}

uint8_t sfeQwiicUltrasonic::getAddress()
{
    return _theBus->address();
}
