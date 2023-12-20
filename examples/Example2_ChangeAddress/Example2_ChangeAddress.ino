#include "SparkFun_Qwiic_Ultrasonic_Arduino_Library.h"

// Create an ultrasonic sensor object
QwiicUltrasonic myUltrasonic;

// Here we set the device address. Note that an older version of the Qwiic
// Ultrasonic firmware used a default address of 0x00. If yours uses 0x00,
// you'll need to change the address below. It is also recommended to run
// Example 2 to change the address to the new default.
uint8_t deviceAddress = kQwiicUltrasonicDefaultAddress; // 0x2F
// uint8_t deviceAddress = 0x00;

void setup()
{
    // Start serial
    Serial.begin(115200);
    Serial.println("Qwiic Ultrasonic Example 2 - Change Address");

    Wire.begin();

    // Attempt to begin the sensor
    while (myUltrasonic.begin(deviceAddress) == false)
    {
        Serial.println("Ultrasonic sensor not connected, check your wiring and I2C address!");
        delay(1000);
    }

    Serial.println("Ultrasonic sensor connected!");

    // Repeat until the address has been successfully changed
    bool addressChanged = false;
    while (addressChanged == false)
    {
        // Print instructions
        Serial.println();
        Serial.println("Please enter a new address for the sensor.");
        Serial.println("Any value between 0x20 and 0x2F is valid.");
        Serial.println("Enter the address in hexadecimal without the `0x`.");
        Serial.println();

        // Clear serial buffer and wait for input
        while (Serial.available() > 0)
            Serial.read();
        while (Serial.available() == 0)
            ;

        // Read input from user
        char input[4]; // Only expecting a few characters
        size_t numBytesRead = Serial.readBytesUntil('\n', input, 4);

        // Parse input using strtoul (STRing TO Unsigned Long integer)
        uint8_t newAddress = strtoul(input, nullptr, 16);

        Serial.print("Parsed address: ");
        Serial.println(newAddress, HEX);

        // Check if the address is valid
        if (newAddress < kQwiicUltrasonicMinAddress || newAddress > kQwiicUltrasonicMaxAddress)
        {
            Serial.println("Invalid address!");
            continue;
        }

        // Address is valid, attempt to change it on the device
        sfeTkError_t err = myUltrasonic.changeAddress(newAddress);

        // Check whether the address was changed successfully
        if (err)
            Serial.println("Failed to change address!");

        // Success, we're done here!
        addressChanged = true;
    }

    Serial.println("Address changed successfully! Continuing...");

    // Wait a moment so user can read the messages
    delay(1000);
}

void loop()
{
    // Get measurement from sensor. Note that the mesaured distance actually
    // comes from the previous trigger, so measurements will be slightly delayed
    uint16_t distance = 0;
    myUltrasonic.triggerAndRead(distance);

    // Print measurement
    Serial.print("Distance (mm): ");
    Serial.println(distance);

    // Wait a bit
    delay(100);
}