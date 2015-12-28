#pragma once

#include "Energia.h"
#include "common.h"

#include "schmitttrigger.h"

// fully charged voltage should be 4.2 per cell, any more and something funny is going on.
const float BATT_MAX_VOLTAGE = 4.6 * BATT_CELL_COUNT;
const float BATT_LOW_VOLTAGE = 3.5 * BATT_CELL_COUNT;
const float BATT_MIN_VOLTAGE = 3.3 * BATT_CELL_COUNT;

const float BATT_SCHMITT_VOLTAGE_WINDOW = 0.05 * BATT_CELL_COUNT;
const float BATT_SCHMITT_CURRENT_WINDOW = 1.0;


// its safe to say that we are running off an external power source here
const float BATT_EXTERNAL_VOLTAGE = 0.5 * BATT_CELL_COUNT;



class Power
{
public:

  Power();
  
  void Init();
  void Update();
  void SetArm(bool arm);

  bool Error();
  void ClearError();

  float voltage;
  float current;

  bool error_overcurrent;
  bool error_overvolt;
  bool error_min_battery;

  bool low_battery;
  bool external_power;

private:

  SchmittTrigger schmitt_overvolt;
  SchmittTrigger schmitt_overcurrent;
  SchmittTrigger schmitt_min_battery;

  SchmittTrigger schmitt_low_battery;
  SchmittTrigger schmitt_battery_present;

};







extern Power power;

