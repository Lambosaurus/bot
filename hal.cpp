#include "hal.h"



HAL::HAL()
{
}

void HAL::Init()
{
  master_on = false;
  master_arm = false;
  arm_timer.Init();

  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);

  SERIAL_BLUE.begin(115200);
  blue_connected = false;
  pinMode(PIN_BLUE_DETECT, INPUT_PULLDOWN);

  drive.Init();
  
  pinMode(PIN_MASTER_LED, OUTPUT);

  master_button.Init(PIN_MASTER_BUTTON);
}


void HAL::SetOn(bool on)
{
  if (SOFTWARE_MASTER_ON)
  {
    master_on = on;
  }

}

bool HAL::GetOn()
{
  return master_on;
}


void HAL::Arm()
{
  if (master_on)
  {
    master_arm = true;
    arm_timer.Zero();
  }
}

void HAL::MaintainArm()
{
  if (master_arm)
  {
    arm_timer.Zero();
  }
}

void HAL::Disarm()
{
  master_arm = false;
}

bool HAL::Armed()
{
  return master_arm;
}

void HAL::Update()
{
  master_button.Update();
  if (master_button.changed && master_button.pressed)
  {
    master_on = !master_on;
  }

  // master_arm requires master_on
  master_arm = master_arm && master_on;

  if (master_arm)
  {
    if (arm_timer.Time() > ARM_MAINTAIN_PERIOD_MS)
    {
      master_arm = false;
    }
  }

  drive.SetArm(master_arm);


  digitalWrite(PIN_MASTER_LED, master_on);

  drive.Update();

  blue_connected = digitalRead(PIN_BLUE_DETECT);
  digitalWrite(PIN_LED_BLUE, blue_connected);
}


bool HAL::Error()
{
  return drive.Error();
}


HAL hal;


