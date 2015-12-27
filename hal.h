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

  void set_master_on(bool on);
  bool get_master_on();


  Drive drive;

private:
  
  bool master_on;
  Button master_button;

  bool blue_connected;
};



extern HAL hal;
