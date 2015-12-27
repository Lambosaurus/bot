#include "drive.h"



Drive::Drive()
{
}

void Drive::init()
{
  front_map.init_bipolar(FRONT_SERVO_MIN, FRONT_SERVO_MAX);
  back_map.init_bipolar(BACK_SERVO_MIN, BACk_SERVO_MAX);

  throttle_map.init_bipolar(-MOTOR_MAX_POWER, MOTOR_MAX_POWER);
  pinMode(PIN_MOTORS_PWM, OUTPUT);
  pinMode(PIN_MOTORS_DIR, OUTPUT);

  hal_master_on = false;

  enabled_flag = true;
  disable();
}



void Drive::enable()
{

  if ( (!enabled_flag) && (!error_flag) && hal_master_on)
  {
    enabled_flag = true;

    front_servo.attach(PIN_FRONT_SERVO);
    back_servo.attach(PIN_BACK_SERVO);

    turn(0.0);
    digitalWrite(PIN_MOTORS_PWM, false);
    digitalWrite(PIN_MOTORS_DIR, false);

  }
}

void Drive::disable()
{
  if (enabled_flag)
  {
    enabled_flag = false;

    front_servo.detach();
    back_servo.detach();

    digitalWrite(PIN_MOTORS_PWM, false);
    digitalWrite(PIN_MOTORS_DIR, false);
  }
}

bool Drive::enabled()
{
  return enabled_flag;
}


void Drive::hold_enable()
{
  if (enabled_flag)
  {
    enable_timer.zero();
  }
}

void Drive::update( bool master_on )
{
  hal_master_on = master_on;
  if (enabled)
  {
    if ( (!hal_master_on) || (enable_timer.time() > DRIVE_ENABLE_TIME))
    {
      disable();
      error_flag = true;
    }
  }
}

void Drive::throttle(float value)
{
  if (enabled_flag)
  {
    int power = throttle_map.map(value);
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

void Drive::slide(float value)
{
  if (enabled_flag)
  {
    front_servo.writeMicroseconds(front_map.map(value));
    back_servo.writeMicroseconds(back_map.map(-value));
  }
}

void Drive::turn(float value)
{
  if (enabled_flag)
  {
    front_servo.writeMicroseconds(front_map.map(value));
    back_servo.writeMicroseconds(back_map.map(value));
  }
}

bool Drive::error()
{
  return error_flag;
}

void Drive::clear_error()
{
  error_flag = false;
}


