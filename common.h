#pragma once


#include "Energia.h"

#define CLAMP(x,low,high) ( max( low, min(x,high) ) )



const byte PIN_BUTTON1 = 31;
const byte PIN_BUTTON2 = 17;

const byte PIN_MASTER_BUTTON = 4;
const byte PIN_MASTER_LED = 3;


const byte PIN_LED_RED = 30;
const byte PIN_LED_GREEN = 39;
const byte PIN_LED_BLUE = 40;


const byte PIN_FRONT_SERVO = 10;
const byte PIN_BACK_SERVO = 11;

const byte PIN_MOTORS_PWM = 12;
const byte PIN_MOTORS_DIR = 14;

const byte PIN_BLUE_DETECT = 13;
#define SERIAL_BLUE Serial2

const unsigned int UPDATE_PERIOD_MS = 5;
const unsigned int ARM_MAINTAIN_PERIOD_MS = 1000;




