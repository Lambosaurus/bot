#pragma once


#include "common.h"
#include "Energia.h"

#include "drive.h"
#include "power.h"
#include "tweeter.h"

#include "button.h"
#include "vmap.h"
#include "timer.h"



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
  Power power;
  Tweeter tweeter;

  bool Error();
  void ClearErrors();

  void SetSoftError(bool state);

private:
  
  bool OkToArm();

  bool soft_error;

  bool master_on;
  bool master_arm;
  Timer arm_timer;

  Button master_button;

  bool blue_connected;
};


extern HAL hal;
