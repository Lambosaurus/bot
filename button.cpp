#include "button.h"



Button::Button()
{
}

void Button::Init( byte arg_pin)
{
  pin = arg_pin;
  ticker.Init(DEBOUNCE_TICKS);
  pinMode(pin, INPUT_PULLUP);
  pressed = false;

  Update();
  changed = false;
}

void Button::Update()
{
  bool new_pressed = !digitalRead(pin);
  changed = false;

  if (new_pressed != pressed)
  {
    if (ticker.Tick())
    {
      pressed = new_pressed;
      changed = true;
    }
  }
  else
  {
    ticker.Clear();
  }
}