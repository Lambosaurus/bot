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

float AnalogReadVoltage(byte pin);



// ------------ // tweeter // ------------ //
const byte PIN_TWEETER = 19;


// ------------ // HAL // ------------ //
const byte PIN_MASTER_BUTTON = 4;
const byte PIN_MASTER_LED = 3;

const bool TWEETER_ALARM_ON_ERROR = true;

const bool ALLOW_SOFT_ERROR = true;
const bool ALLOW_SOFT_MASTER_ON = true;
const bool ALLOW_CLEAR_ERRORS = true;

const unsigned int ARM_MAINTAIN_PERIOD_MS = 1000;
const unsigned int UPDATE_PERIOD_MS = 5;



// ------------ // power // ------------ //
const byte PIN_BATT_VOLTAGE = 26;
const byte PIN_BATT_CURRENT = 25;

const byte BATT_CELL_COUNT = 3;
const float BATT_MAX_CURRENT = 20; // I can go up to 40 safely i think

const float BATT_VOLTAGE_SENSE_MULTIPLIER = 5.534; // This seems to be +/- 1%. Is from a voltage divider of 15.0k 68.8k


const float BATT_CURRENT_SENSE_AMP = 22.0;
const float BATT_CURRENT_SENSE_RESISTANCE = 0.005;

const float BATT_CURRENT_SENSE_MULTIPLIER = 1.0 / (BATT_CURRENT_SENSE_AMP * BATT_CURRENT_SENSE_RESISTANCE);
const float BATT_CURRENT_SENSE_OFFSET = 0.17;



// ------------ // drive // ------------ //
const byte PIN_FRONT_SERVO = 10;
const byte PIN_BACK_SERVO = 11;

const byte PIN_MOTORS_PWM = 12;
const byte PIN_MOTORS_DIR = 14;

// ------------ // blue // ------------ //
const byte PIN_BLUE_DETECT = 13;
#define SERIAL_BLUE Serial2



