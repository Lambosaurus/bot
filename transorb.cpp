#include "transorb.h"



Transorb::Transorb()
{
  ticks = 0;
}

void Transorb::Init(unsigned int length, bool default_state)
{
  max_ticks = length;
  high = default_state;
}


bool Transorb::Update(bool state)
{
  if (state != high)
  {
    if (ticks++ >= max_ticks)
    {
      high = state;
      ticks = 0;
    }
  }
  else
  {
    ticks = 0;
  }
  return high;
}



