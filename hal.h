#pragma once


#include "common.h"
#include "Energia.h"

#include "drive.h"
#include "button.h"

#include "vmap.h"
#include "timer.h"



const bool SOFTWARE_MASTER_ON = true;

class HAL
{
public:
  HAL();

  void Init();
  void Update();

  void SetOn(bool on);
  bool GetOn();

  void Arm();
  void MaintainArm();
  void Disarm();
  bool Armed();

  Drive drive;

  bool Error();

private:
  
  bool master_on;
  bool master_arm;
  Timer arm_timer;

  Button master_button;

  bool blue_connected;
};



extern HAL hal;
