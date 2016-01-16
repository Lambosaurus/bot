#pragma once

#include "common.h"
#include "Energia.h"
#include "driverlib\watchdog.h"




class Watchdog
{
public:
  Watchdog();
  void Init();
  void Kick();

  void ForceReset(); // we cause a reset, by stalling here
};

