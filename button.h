#pragma once


#include "Energia.h"
#include "ticker.h"

const unsigned int DEBOUNCE_TICKS = 8;

class Button
{
public:
  Button();

  void Init(byte arg_pin);
  void Update();

  bool pressed;
  bool changed;

private:
  byte pin;
  Ticker ticker;
};

