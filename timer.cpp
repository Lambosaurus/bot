#include "timer.h"




Timer::Timer()
{

}

void Timer::init()
{
  zero();
}

void Timer::zero()
{
  zeroed_time = millis();
}

unsigned long Timer::time()
{
  return millis() - zeroed_time;
}



Periodic::Periodic()
{

}

void Periodic::init(unsigned long arg_period)
{
  period = arg_period;
  next_event = millis() + period;
}

void Periodic::zero()
{
  next_event = millis() + period;
}

bool Periodic::elapsed()
{
  if (millis() > next_event)
  {
    next_event += period;
    return true;
  }
  return false;
}

