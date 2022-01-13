/*
  This is a library written for the Qwiic Soil Moisture Sensor.
  By Frank Giger, Janurary 06th, 2022
*/

#include "QwiicSoilMoistureSensor.h"

// Constructor
SoilMoistureSensor::SoilMoistureSensor() {
    _SoilSensorAddress = 0;
}

//Start I2C communication
boolean SoilMoistureSensor::begin(uint8_t address, TwoWire &wirePort) {
  if (address < 0x08 || address > 0x77) return false; //invalid I2C addresses
  _SoilSensorAddress = address; //store the address in a private global variable
  _i2cPort = &wirePort; //Grab which port the user wants us to use		
  
 return isConnected();
}

boolean SoilMoistureSensor::isConnected() {
  _i2cPort->beginTransmission(_SoilSensorAddress);
  if (_i2cPort->endTransmission() == 0)
    return true;
  return false;
}

void SoilMoistureSensor::ledOff() {
  _i2cPort->beginTransmission(_SoilSensorAddress);
  _i2cPort->write(COMMAND_LED_OFF);
  _i2cPort->endTransmission();
}

void SoilMoistureSensor::ledOn() {
  _i2cPort->beginTransmission(_SoilSensorAddress);
  _i2cPort->write(COMMAND_LED_ON);
  _i2cPort->endTransmission();
}

uint16_t SoilMoistureSensor::readSoil() {
    _i2cPort->beginTransmission(_SoilSensorAddress);
    _i2cPort->write(COMMAND_GET_VALUE);
    _i2cPort->endTransmission();

    _i2cPort->requestFrom(_SoilSensorAddress, 2);

    while(_i2cPort->available()) {
        uint8_t ADC_VALUE_L = _i2cPort->read();
        //Serial.print("ADC_VALUE_L: ");
        //Serial.println(ADC_VALUE_L, DEC);
        uint8_t ADC_VALUE_H = _i2cPort->read();
        //Serial.print("ADC_VALUE_H: ");
        //Serial.println(ADC_VALUE_H, DEC);

        uint16_t ADC_VALUE = 0;
        ADC_VALUE = ADC_VALUE_H;
        ADC_VALUE<<=8;
        ADC_VALUE|=ADC_VALUE_L;
        //Serial.print("ADC_VALUE: ");
        //Serial.println(ADC_VALUE, DEC);
        return ADC_VALUE;
    }
}

//Change the I2C address from one address to another
boolean SoilMoistureSensor::changeAddress(uint8_t newAddress)
{
  _i2cPort->beginTransmission(_SoilSensorAddress); //Communicate using the old address
  _i2cPort->write(COMMAND_CHANGE_ADDRESS); //0xC7 is the register location on the KeyPad to change its I2C address
  _i2cPort->write(newAddress); //Go to the new address
  if (_i2cPort->endTransmission() != 0)
  {
    //Sensor did not ACK
    return (false);
  }
    _SoilSensorAddress = newAddress;
	return (true);
}