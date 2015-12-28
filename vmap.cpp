#include "vmap.h"



Vmap::Vmap()
{
}

void Vmap::InitMonopolar(int arg_min, int arg_max)
{
  vmin = arg_min;
  vmax = arg_max;

  fmin = 0.0;
  vdelta = vmax - vmin;
}

void Vmap::InitBipolar(int arg_min, int arg_max)
{
  vmin = arg_min;
  vmax = arg_max;

  fmin = -1.0;
  vdelta = (vmax - vmin)/2;
}

int Vmap::Map(float value)
{
  value = CLAMP(value, fmin, 1.0);
  return vmin + (vdelta*value);
}
















