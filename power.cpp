#include "power.h"



Power::Power()
{
  // these are safe when high, so the window is on the high side
  schmitt_battery_present.Init(BATT_MIN_VOLTAGE, BATT_MIN_VOLTAGE + BATT_SCHMITT_VOLTAGE_WINDOW);
  schmitt_low_battery.Init(BATT_LOW_VOLTAGE, BATT_LOW_VOLTAGE + BATT_SCHMITT_VOLTAGE_WINDOW);
  schmitt_min_battery.Init(BATT_EXTERNAL_VOLTAGE, BATT_EXTERNAL_VOLTAGE + BATT_SCHMITT_VOLTAGE_WINDOW);

  // these are safe when low, so the window is on the low side
  schmitt_overvolt.Init(BATT_MAX_VOLTAGE - BATT_SCHMITT_VOLTAGE_WINDOW, BATT_LOW_VOLTAGE);
  schmitt_overcurrent.Init(BATT_MAX_CURRENT - BATT_SCHMITT_CURRENT_WINDOW, BATT_MAX_CURRENT);
}

void Power::Init()
{
  pinMode(PIN_BATT_VOLTAGE, INPUT);
  pinMode(PIN_BATT_CURRENT, INPUT);

  current_average.Init(average_buffer, BATT_VOLTAGE_BUFFER_LENGTH);
}

void Power::Update()
{
  // i'll have to watch these values, im not sure how accurate the ADC is.
  // it may pay to put them through an averager

  float sense_voltage = AnalogReadVoltage(PIN_BATT_VOLTAGE);
  voltage = sense_voltage * BATT_VOLTAGE_SENSE_MULTIPLIER;

  float sense_current = AnalogReadVoltage(PIN_BATT_CURRENT);
  
  current_average.Add( (sense_current - BATT_CURRENT_SENSE_OFFSET) * BATT_CURRENT_SENSE_MULTIPLIER );
  current = current_average.Average();

  schmitt_overvolt.Update(voltage);
  schmitt_overcurrent.Update(current);
  schmitt_min_battery.Update(voltage);

  schmitt_low_battery.Update(voltage);
  schmitt_battery_present.Update(voltage);


  external_power = !schmitt_battery_present.high;
  low_battery = !schmitt_low_battery.high && !external_power;

  if (schmitt_overvolt.high) { error_overvolt = true; }
  if (schmitt_overcurrent.high) { error_overcurrent = true; }
  if (!schmitt_min_battery.high && !external_power) { error_min_battery = true; }

}


void Power::SetArm(bool arm)
{
}

bool Power::Error()
{
  return error_min_battery || error_overvolt || error_overcurrent;
}

void Power::ClearError()
{
  error_min_battery = false;
  error_overvolt = false;
  error_overcurrent = false;
}



