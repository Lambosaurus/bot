#include "drive.h"



Drive::Drive()
{
}

void Drive::Init()
{
  front_map.InitBipolar(FRONT_SERVO_MIN, FRONT_SERVO_MAX);
  back_map.InitBipolar(BACK_SERVO_MIN, BACk_SERVO_MAX);

  throttle_map.InitBipolar(-MOTOR_MAX_POWER, MOTOR_MAX_POWER);
  pinMode(PIN_MOTORS_PWM, OUTPUT);
  pinMode(PIN_MOTORS_DIR, OUTPUT);

  enabled = false;
}



void Drive::Enable()
{

  if ( (!enabled) && (!Error()) && armed)
  {
    enabled = true;

    // enable the servos
    front_servo.attach(PIN_FRONT_SERVO);
    back_servo.attach(PIN_BACK_SERVO);
    
    Turn(0.0); // center wheels
    // maybe i could have it return to last

    // motors off!
    digitalWrite(PIN_MOTORS_PWM, false);
    digitalWrite(PIN_MOTORS_DIR, false);
  }
}

void Drive::Disable()
{
  if (enabled)
  {
    enabled = false;

    // disable the servos
    front_servo.detach();
    back_servo.detach();

    // motors off!
    digitalWrite(PIN_MOTORS_PWM, false);
    digitalWrite(PIN_MOTORS_DIR, false);
  }
}


void Drive::SetArm(bool arm)
{
  // if enabled and disarmed, it should Disarm() on the next Update()
  armed = arm;
}

void Drive::Update()
{
  if (enabled && (!armed))
  {
    Disable();
  }
  else if ((!enabled) and armed)
  {
    Enable();
  }
}

void Drive::Throttle(float value)
{
  if (enabled)
  {
    int power = throttle_map.Map(value);
    bool reverse = false;

    if (power < 0)
    {
      reverse = true;
      power = -power;
    }

    if (power < MOTOR_MIN_POWER)
    {
      analogWrite(PIN_MOTORS_PWM, 0);
      // i set this up so that the motor DIR pin is not toggled if the power is zero
    }
    else
    {
      analogWrite(PIN_MOTORS_PWM, power);
      digitalWrite(PIN_MOTORS_DIR, reverse);
    }
  }
}

void Drive::Slide(float value)
{
  if (enabled)
  {
    front_servo.writeMicroseconds(front_map.Map(value));
    back_servo.writeMicroseconds(back_map.Map(-value));
  }
}

void Drive::Turn(float value)
{
  if (enabled)
  {
    front_servo.writeMicroseconds(front_map.Map(value));
    back_servo.writeMicroseconds(back_map.Map(value));
  }
}

bool Drive::Error()
{
  return false;
}

void Drive::ClearError()
{
}


