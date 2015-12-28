#pragma once

#include "Energia.h"
#include "common.h"

class Timer
{
public:
  Timer();

  void Init();

  inline void Zero(); // zeros the clock
  inline unsigned long Time(); // returns the time elapsed

private:
  unsigned long zeroed_time;
};


class Periodic
{
public:
  Periodic();

  void Init(unsigned long arg_period);
  inline void Zero(); // zeros the clock
  inline bool Elapsed(); // returns true if the period has elapsed, and schedules the next time
private:
  unsigned long next_event;
  unsigned long period;
};



