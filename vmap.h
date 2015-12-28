#pragma once


#include "common.h"


class Vmap
{
public:

  Vmap();

  void InitMonopolar(int arg_min, int arg_max);
  void InitBipolar(int arg_min, int arg_max);

  int Map(float value);


private:

  float fmin;

  int vmin;
  int vmax;
  int vdelta;

};



