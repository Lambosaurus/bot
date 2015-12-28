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

  void Init();
  void Update();
  
  void SetArm(bool arm);

  void Turn(float angle);
  void Slide(float angle);
  void Throttle(float throttle);

  bool Error();
  void ClearError();

private:

  void Enable();
  void Disable();

  Vmap throttle_map;

  Vmap front_map;
  Vmap back_map;
  Servo front_servo;
  Servo back_servo;

  bool enabled;
  bool armed;
};

