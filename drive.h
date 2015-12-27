#pragma once


#include "Energia.h"
#include "Servo.h"

#include "common.h"
#include "vmap.h"
#include "timer.h"


const unsigned int DRIVE_ENABLE_TIME = 500;


const byte FRONT_SERVO_MIN = 2000;
const byte FRONT_SERVO_MAX = 2000;
const byte BACK_SERVO_MIN = 1000;
const byte BACk_SERVO_MAX = 1000;

const int MOTOR_MAX_POWER = 255;
const int MOTOR_MIN_POWER = 60;



class Drive
{

public:
  Drive();

  void init();
  void update(bool master_on);

  void enable();
  void hold_enable();
  void disable();
  bool enabled();
  
  void turn(float angle);
  void slide(float angle);
  void throttle(float throttle);

  bool error();
  void clear_error();

private:

  Vmap throttle_map;

  Vmap front_map;
  Vmap back_map;
  Servo front_servo;
  Servo back_servo;

  Timer enable_timer;
  bool enabled_flag;

  bool error_flag;

  bool hal_master_on;
};

