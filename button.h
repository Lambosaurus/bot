#pragma once


#include "Energia.h"
#include "ticker.h"

const unsigned int DEBOUNCE_TICKS = 8;

class Button
{
public:
  Button();

  void init(byte arg_pin);

  void update();

  bool pressed;
  bool changed;

private:
  byte pin;
  Ticker ticker;
};

