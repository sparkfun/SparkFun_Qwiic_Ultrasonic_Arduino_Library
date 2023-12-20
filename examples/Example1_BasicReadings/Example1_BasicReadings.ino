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
    Serial.println("Qwiic Ultrasonic Example 1 - Basic Readings");

    Wire.begin();

    // Attempt to begin the sensor
    while (myUltrasonic.begin(deviceAddress) == false)
    {
        Serial.println("Ultrasonic sensor not connected, check your wiring and I2C address!");
        delay(1000);
    }

    Serial.println("Ultrasonic sensor connected!");
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