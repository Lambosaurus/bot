#pragma once

#include "Energia.h"
#include "common.h"

class Timer
{
public:
  Timer();

  void init();

  void zero();
  unsigned long time();

private:
  unsigned long zeroed_time;
};


class Periodic
{
public:
  Periodic();

  void init(unsigned long arg_period);
  void zero();
  bool elapsed();
private:
  unsigned long next_event;
  unsigned long period;
};



