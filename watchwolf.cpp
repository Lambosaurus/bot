#include "watchwolf.h"
#include "driverlib\sysctl.h"



volatile bool watchdog_flag = true;

// this occurrs on the watchdog period
void WatchdogISR()
{
  if (watchdog_flag)
  {
    watchdog_flag = false; // must be kicked again

    // we clear this, to prevent a reset
    WatchdogIntClear(WATCHDOG0_BASE);
  }

  // if this ISR occurrs, and the interrupt was not cleared last time
  // then a reset will occurr
}




Watchdog::Watchdog()
{
}

void Watchdog::Init()
{

  SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);

  WatchdogReloadSet(WATCHDOG0_BASE, (SysCtlClockGet()*WATCHDOG_PERIOD) / 1000);
  
  WatchdogIntRegister(WATCHDOG0_BASE, WatchdogISR);
  WatchdogIntClear(WATCHDOG0_BASE);

  WatchdogIntEnable(WATCHDOG0_BASE);
  WatchdogResetEnable(WATCHDOG0_BASE);
  WatchdogEnable(WATCHDOG0_BASE);
  
  Kick();
}

void Watchdog::Kick()
{
  watchdog_flag = true;
}

void Watchdog::ForceReset()
{
  watchdog_flag = false;
  while (1); // now... we wait..
}