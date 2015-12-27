#pragma once


#include "Energia.h"
#include "Servo.h"

#include "common.h"
#include "vmap.h"
#include "timer.h"


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
  void update();
  
  void set_arm(bool arm);

  void turn(float angle);
  void slide(float angle);
  void throttle(float throttle);

  bool error();
  void clear_error();

private:

  void enable();
  void disable();

  Vmap throttle_map;

  Vmap front_map;
  Vmap back_map;
  Servo front_servo;
  Servo back_servo;

  bool error_flag;

  bool enabled_flag;
  bool arm_flag;
};

