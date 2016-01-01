#pragma once

#include "Energia.h"
#include "timer.h"

const unsigned int TWEETER_ERROR_HIGH_PERIOD = 250;
const unsigned int TWEETER_ERROR_LOW_PERIOD = 500;

const unsigned int TWEETER_BATTERY_HIGH_PERIOD = 500;
const unsigned int TWEETER_BATTERY_LOW_PERIOD = 500;

const unsigned int TWEETER_CHIRP_HIGH_PERIOD = 100;
const unsigned int TWEETER_CHIRP_LOW_PERIOD = 50;


class Tweeter
{
public:
  Tweeter();

  void Init();
  void Update();
  void SetArm(bool arm);

  void Chirp(byte count);
  void SetErrorAlarm(bool state);
  void SetBatteryAlarm(bool state);
  
  bool Error();
  void ClearError();

  bool ErrorAlarmOn();
  bool BatteryAlarmOn();

private:

  bool err_alarm;
  bool batt_alarm;

  byte chirp_counter;
  bool chirp_high;
  Timer chirp_timer;

};

