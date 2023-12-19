#include "sfeQwiicUltrasonic.h"

sfeQwiicUltrasonic::sfeQwiicUltrasonic()
{
    _theBus = nullptr;
}

sfeTkError_t sfeQwiicUltrasonic::begin(sfeTkII2C *theBus)
{
    // Nullptr check
    if (theBus == nullptr)
        return kSTkErrFail;

    // Check the device address
    if (theBus->address() < QWIIC_ULTRASONIC_MIN_ADDRESS || theBus->address() > QWIIC_ULTRASONIC_MAX_ADDRESS)
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

sfeTkError_t sfeQwiicUltrasonic::triggerAndRead(uint16_t &distance)
{
    size_t bytesRead = 0;
    uint8_t rawData[2] = {0, 0};

    // Attempt to read the distance
    sfeTkError_t err = _theBus->readRegisterRegion(QWIIC_ULTRASONIC_REGISTER_TRIGGER, rawData, 2, bytesRead);

    // Check whether the read was successful
    if (err)
        return err;

    // Check whether all data was read
    if (bytesRead != 2)
        return kSTkErrFail;

    // Store raw data
    distance = (rawData[0] << 8) | rawData[1];

    // Done!
    return kSTkErrOk;
}

sfeTkError_t sfeQwiicUltrasonic::changeAddress(uint8_t address)
{
    // Check whether the address is valid
    if (address < QWIIC_ULTRASONIC_MIN_ADDRESS || address > QWIIC_ULTRASONIC_MAX_ADDRESS)
        return kSTkErrFail;

    // The first bit of the address must be set to 1
    address |= 0x80;

    // Write the new address to the device
    sfeTkError_t err = _theBus->writeByte(address);

    // Check whether the write was successful
    if (err)
        return err;

    // Update the address in the bus
    _theBus->setAddress(address);

    // Done!
    return kSTkErrOk;
}
