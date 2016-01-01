#include "common.h"



float AnalogReadVoltage(byte pin)
{
  return analogRead(pin) * (ADC_MAX_VOLTAGE / ADC_MAX_VALUE);
}




















