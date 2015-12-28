#include "power.h"



Power::Power()
{
  // these are safe when high, so the window is on the high side
  schmitt_battery_present.Init(BATT_MIN_VOLTAGE, BATT_MIN_VOLTAGE + BATT_SCHMITT_VOLTAGE_WINDOW);
  schmitt_low_battery.Init(BATT_LOW_VOLTAGE, BATT_LOW_VOLTAGE + BATT_SCHMITT_VOLTAGE_WINDOW);
  schmitt_min_battery.Init(BATT_NOTPRESENT_VOLTAGE, BATT_NOTPRESENT_VOLTAGE + BATT_SCHMITT_VOLTAGE_WINDOW);

  // these are safe when low, so the window is on the low side
  schmitt_overvolt.Init(BATT_MAX_VOLTAGE - BATT_SCHMITT_VOLTAGE_WINDOW, BATT_LOW_VOLTAGE);
  schmitt_overcurrent.Init(BATT_MAX_CURRENT - BATT_SCHMITT_CURRENT_WINDOW, BATT_MAX_CURRENT);
}

void Power::Init()
{
  pinMode(PIN_BATT_VOLTAGE, INPUT);
  pinMode(PIN_BATT_CURRENT, INPUT);
}

void Power::Update()
{
  unsigned int raw_voltage = analogRead(PIN_BATT_VOLTAGE);
  unsigned int raw_current = analogRead(PIN_BATT_CURRENT);
}

void Power::SetArm(bool arm)
{
  // power never sleeps
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













Power power;

