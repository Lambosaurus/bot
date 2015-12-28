#include "hal.h"



HAL::HAL()
{
}

void HAL::init()
{
  master_on = false;
  master_arm = false;
  arm_timer.init();

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


void HAL::set_on(bool on)
{
  if (SOFTWARE_MASTER_ON)
  {
    master_on = on;
  }

}

bool HAL::get_on()
{
  return master_on;
}


void HAL::arm()
{
  if (master_on)
  {
    master_arm = true;
    arm_timer.zero();
  }
}

void HAL::maintain_arm()
{
  if (master_arm)
  {
    arm_timer.zero();
  }
}

void HAL::disarm()
{
  master_arm = false;
}

bool HAL::armed()
{
  return master_arm;
}

void HAL::update()
{
  master_button.update();
  if (master_button.changed && master_button.pressed)
  {
    master_on = !master_on;
  }

  // master_arm requires master_on
  master_arm = master_arm && master_on;

  if (master_arm)
  {
    if (arm_timer.time() > ARM_MAINTAIN_PERIOD_MS)
    {
      master_arm = false;
    }
  }

  drive.set_arm(master_arm);


  digitalWrite(PIN_MASTER_LED, master_on);

  drive.update();

  blue_connected = digitalRead(PIN_BLUE_DETECT);
  digitalWrite(PIN_LED_BLUE, blue_connected);
}


bool HAL::error()
{
  return drive.error();
}


HAL hal;


