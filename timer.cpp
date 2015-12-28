#include "timer.h"




Timer::Timer()
{

}

void Timer::Init()
{
  Zero();
}

inline void Timer::Zero()
{
  zeroed_time = millis();
}

inline unsigned long Timer::Time()
{
  return millis() - zeroed_time;
}



Periodic::Periodic()
{

}

void Periodic::Init(unsigned long arg_period)
{
  period = arg_period;
  Zero();
}

inline void Periodic::Zero()
{
  next_event = millis() + period;
}

inline bool Periodic::Elapsed()
{
  if (millis() > next_event)
  {
    next_event += period;
    return true;
  }
  return false;
}

