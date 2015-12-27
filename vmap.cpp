#include "vmap.h"



Vmap::Vmap()
{
}

void Vmap::init_monopolar(int arg_min, int arg_max)
{
  vmin = arg_min;
  vmax = arg_max;

  fmin = 0.0;
  vdelta = vmax - vmin;
}

void Vmap::init_bipolar(int arg_min, int arg_max)
{
  vmin = arg_min;
  vmax = arg_max;

  fmin = -1.0;
  vdelta = (vmax - vmin)/2;
}

int Vmap::map(float value)
{
  value = CLAMP(value, fmin, 1.0);
  return vmin + (vdelta*value);
}
















