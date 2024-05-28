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

sfeTkError_t sfeQwiicUltrasonic::getDistace(uint16_t &distance)
{
    size_t bytesRead = 0;
    uint8_t rawData[2] = {0, 0};

    // Attempt to read the distance
    sfeTkError_t err = _theBus->write(kQwiicUltrasonicRegisterTrigger, rawData, 2, bytesRead);
    sfeTkError_t err = _theBus->readRegisterRegion(kQwiicUltrasonicRegisterTrigger, rawData, 2, bytesRead);

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
    sfeTkError_t err = _theBus->readRegisterRegion(kQwiicUltrasonicRegisterTrigger, rawData, 2, bytesRead);

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

uint8_t sfeQwiicUltrasonic::getAddress()
{
    return _theBus->address();
}
