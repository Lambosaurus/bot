#pragma once


#include "Energia.h"

#define CLAMP(x,low,high) ( max( low, min(x,high) ) )


// ------------ // TivaC board // ------------ //
const byte PIN_BUTTON1 = 31;
const byte PIN_BUTTON2 = 17;
const byte PIN_LED_RED = 30;
const byte PIN_LED_GREEN = 39;
const byte PIN_LED_BLUE = 40;

const unsigned int ADC_MAX_VALUE = 4096-1;
const float ADC_MAX_VOLTAGE = 3.3;


float AnalogReadVoltage(byte pin)
{
  return analogRead(pin) * (ADC_MAX_VOLTAGE / ADC_MAX_VALUE);
}


// ------------ // master button // ------------ //
const byte PIN_MASTER_BUTTON = 4;
const byte PIN_MASTER_LED = 3;


// ------------ // power // ------------ //
const byte PIN_BATT_VOLTAGE = 25;
const byte PIN_BATT_CURRENT = 26;

const byte BATT_CELL_COUNT = 3;
const float BATT_MAX_CURRENT = 20; // I can go up to 40 safely i think

const float BATT_VOLTAGE_SENSE_MULTIPLIER = 6.30; // This seems to be +/- 1%. Is from a voltage divider of 5.0k 26.8k


// Current passes through a 0.005 Ohm sense resistor
// So, should be a 16x amplifier, but the result will read as 15x, as the amplifier ground is before the sense resistor

// I popped my multimeters 10A fuse while calibrating this....
// ya, like +/- 10% here... Will need to calibrate again later.
const float BATT_CURRENT_SENSE_MULTIPLIER = 13.3;



// ------------ // drive // ------------ //
const byte PIN_FRONT_SERVO = 10;
const byte PIN_BACK_SERVO = 11;

const byte PIN_MOTORS_PWM = 12;
const byte PIN_MOTORS_DIR = 14;

// blue
const byte PIN_BLUE_DETECT = 13;
#define SERIAL_BLUE Serial2

// arm time
const unsigned int ARM_MAINTAIN_PERIOD_MS = 1000;

// main loop
const unsigned int UPDATE_PERIOD_MS = 5;




