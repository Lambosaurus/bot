#include "button.h"



Button::Button()
{
}

void Button::init( byte arg_pin)
{
  pin = arg_pin;
  ticker.init(DEBOUNCE_TICKS);
  pinMode(pin, INPUT_PULLUP);
  pressed = false;

  update();
  changed = false;
}

void Button::update()
{
  bool new_pressed = !digitalRead(pin);
  changed = false;

  if (new_pressed != pressed)
  {
    if (ticker.tick())
    {
      pressed = new_pressed;
      changed = true;
    }
  }
  else
  {
    ticker.clear();
  }
}