/*
  This is a library written for the Qwiic Soil Moisture Sensor.
  By Frank Giger, Janurary 06th, 2022
*/

#ifndef Qwiic_Soil_Moisture_Sensor_h
#define Qwiic_Soil_Moisture_Sensor_h

#include "Arduino.h"
#include <Wire.h>

#define COMMAND_CHANGE_ADDRESS (0xC7)
#define COMMAND_LED_OFF (0x00)
#define COMMAND_LED_ON (0x01)
#define COMMAND_GET_VALUE (0x05)
#define COMMAND_NOTHING_NEW (0x99)

class SoilMoistureSensor {
    public:
	SoilMoistureSensor();
    //Initialize parameters such as I2C address and port for communication
	boolean begin(uint8_t address = 0x28, TwoWire &wirePort = Wire);//If user doesn't specificy then 0x23 and Wire will be used
	
	//Test I2C connection on I2C address
	boolean isConnected();

  uint16_t readSoil();

    // Turn on the LED on the sensor board
    void ledOn();

    // Turn off the LED on the sensor
    void ledOff();
  
	//Change the I2C address from one address to another
	boolean changeAddress(uint8_t newAddress);

  private:
	//This stores the current I2C address of the LED Stick
    uint8_t _SoilSensorAddress;
	//This stores the requested i2c port
	TwoWire * _i2cPort;
};

#endif