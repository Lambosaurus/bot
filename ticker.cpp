#include "ticker.h"



Ticker::Ticker()
{
}


void Ticker::Init(unsigned int arg_max_ticks)
{
  tick_max = arg_max_ticks;
}

bool Ticker::Tick()
{
  if (++ticks >= tick_max)
  {
    ticks = 0;
    return true;
  }
  return false;
}

bool Ticker::Tick(unsigned int elapsed)
{
  unsigned int r = tick_max - ticks;

  if (elapsed >= r)
  {
    ticks = elapsed - r;
    return true;
  }
  
  ticks += elapsed;
  return false;
}

void Ticker::Clear()
{
  ticks = 0;
}