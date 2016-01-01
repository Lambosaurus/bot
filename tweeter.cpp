#include "tweeter.h"




Tweeter::Tweeter()
{
  chirp_counter = 0;
  chirp_high = false;
  
  err_alarm = false;
  batt_alarm = false;

  chirp_timer.Init();
}

void Tweeter::Init()
{
  pinMode(PIN_TWEETER, OUTPUT);
  digitalWrite(PIN_TWEETER, false);
}

void Tweeter::Update()
{
  if (chirp_counter || err_alarm || batt_alarm)
  {
    if (chirp_high)
    {

      unsigned int high_period = (chirp_counter) ? TWEETER_CHIRP_HIGH_PERIOD :
        ((batt_alarm) ? TWEETER_BATTERY_HIGH_PERIOD : TWEETER_ERROR_HIGH_PERIOD);

      if (chirp_timer.Time() > high_period)
      {
        if (chirp_counter) { chirp_counter--; }
        chirp_high = false; 
        chirp_timer.Zero();
      }
    }
    else
    {
      unsigned int low_period = (chirp_counter) ? TWEETER_CHIRP_LOW_PERIOD :
        ((batt_alarm) ? TWEETER_BATTERY_LOW_PERIOD : TWEETER_ERROR_LOW_PERIOD);

      if (chirp_timer.Time() > low_period)
      {
        chirp_high = true;
        chirp_timer.Zero();
      }
    }
    digitalWrite(PIN_TWEETER, chirp_high);
  }
  else
  {
    digitalWrite(PIN_TWEETER, false);
  }

}

void Tweeter::SetErrorAlarm(bool state)
{
  err_alarm = state;
}

bool Tweeter::ErrorAlarmOn()
{
  return err_alarm;
}

void Tweeter::SetBatteryAlarm(bool state)
{
  batt_alarm = state;
}

bool Tweeter::BatteryAlarmOn()
{
  return batt_alarm;
}

void Tweeter::Chirp(byte count)
{
  chirp_counter = count;
  chirp_high = !(err_alarm || batt_alarm);
  chirp_timer.Zero();
}


void Tweeter::SetArm(bool arm)
{
}

bool Tweeter::Error()
{
  return false;
}

void Tweeter::ClearError()
{
}











