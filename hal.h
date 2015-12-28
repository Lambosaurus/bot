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

  void init();
  void update();

  void set_on(bool on);
  bool get_on();

  void arm();
  void maintain_arm();
  void disarm();
  bool armed();

  Drive drive;

  bool error();

private:
  
  bool master_on;
  bool master_arm;
  Timer arm_timer;

  Button master_button;

  bool blue_connected;
};



extern HAL hal;
