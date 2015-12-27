#pragma once


#include "common.h"


class Vmap
{
public:

  Vmap();

  void init_monopolar(int arg_min, int arg_max);
  void init_bipolar(int arg_min, int arg_max);

  int map(float value);


private:

  float fmin;

  int vmin;
  int vmax;
  int vdelta;

};



