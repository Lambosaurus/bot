#include "hal.h"



HAL::HAL()
{
}

void HAL::init()
{
  master_on = false;

  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);

  SERIAL_BLUE.begin(115200);
  blue_connected = false;
  pinMode(PIN_BLUE_DETECT, INPUT_PULLDOWN);

  drive.init();
  
  pinMode(PIN_MASTER_LED, OUTPUT);

  master_button.init(PIN_MASTER_BUTTON);
}


void HAL::set_master_on(bool on)
{
  if (SOFTWARE_MASTER_ON)
  {
    master_on = on;
  }

}

bool HAL::get_master_on()
{
  return master_on;
}


void HAL::update()
{
  master_button.update();
  if (master_button.changed && master_button.pressed)
  {
    master_on = !master_on;
  }
  digitalWrite(PIN_MASTER_LED, master_on);

  drive.update(master_on);

  blue_connected = digitalRead(PIN_BLUE_DETECT);
  digitalWrite(PIN_LED_BLUE, blue_connected);

}



HAL hal;


