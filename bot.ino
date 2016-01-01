
#include "Energia.h"
#include "Servo.h"


#include "common.h"
#include "commkeys.h"

#include "vmap.h"
#include "timer.h"
#include "ticker.h"
#include "schmitttrigger.h"
#include "blockaverage.h"
#include "minipack.h"

#include "hal.h"
#include "power.h"
#include "drive.h"


MinipackInput miniin;
MinipackOutput miniout;

bool green = false;

void dbg()
{
  green = !green;
  digitalWrite(PIN_LED_GREEN, green);
}

void ProcessComm(byte length)
{
  byte key = miniin.Unpack(1);

  if (key == CMD_ACK) {
    if (length == 1)
    {
      if (!miniin.UnpackError())
      {
        miniout.NewPacket();
        miniout.Pack(1, RESPONSE_ACK);
        SERIAL_BLUE.write(miniout.EndPacket());
      }
    }
  }

  else if (key == CMD_ENABLE) {
    if (length == 2)
    {
      byte enable_state = miniin.Unpack(1);
      if (!miniin.UnpackError())
      {
        hal.SetOn(enable_state);
      }
    }
  }

  else if (key == CMD_SOFT_ERR) {
    if (length == 2)
    {
      byte error_state = miniin.Unpack(1);
      if (!miniin.UnpackError())
      {
        hal.SetSoftError(error_state);
      }
    }
  }

  else if (key == CMD_STATUS) {
    if (length == 1)
    {
      if (!miniin.UnpackError())
      {
        byte status =
          (hal.Error() << RESPONSE_STATUS_BIT_ERROR) |
          (hal.GetOn() << RESPONSE_STATUS_BIT_MASTER_ON) |
          (hal.Armed() << RESPONSE_STATUS_BIT_ARMED) |
          (hal.power.low_battery << RESPONSE_STATUS_BIT_LOW_VOLTAGE);


        miniout.NewPacket();
        miniout.Pack(1, RESPONSE_STATUS);
        miniout.Pack(1, status);
        SERIAL_BLUE.write(miniout.EndPacket());
      }
    }
  }

  else if (key == CMD_GET_POWER) {
    if (length == 1)
    {
      if (!miniin.UnpackError())
      {
        miniout.NewPacket();
        miniout.Pack(1, RESPONSE_GET_POWER);
        miniout.PackFloat(hal.power.voltage);
        miniout.PackFloat(hal.power.current);
        SERIAL_BLUE.write(miniout.EndPacket());
      }
    }
  }

  else if (key == CMD_CHIRP) {
    if (length == 2)
    {
      byte chirps = miniin.Unpack(1);
      if (!miniin.UnpackError())
      {
        hal.tweeter.Chirp(chirps);
      }
    }
  }

  else if (hal.GetOn())
  { // commands past this point require master on   
  
    if (key == CMD_ARM) {
      if (length == 2)
      {
        byte arm_cmd = miniin.Unpack(1);
        if (!miniin.UnpackError())
        {
          if (arm_cmd == CMD_ARM_OPEN)
          {
            hal.Arm();
          }
          else if (arm_cmd == CMD_ARM_MAINTAIN)
          {
            hal.MaintainArm();
          }
          else if (arm_cmd == CMD_ARM_CLOSE)
          {
            hal.Disarm();
          }
        }
      }
    }

    else if (key == CMD_THROTTLE) {
      if (length == 3)
      {
        float throttle = miniin.UnpackFloat();
        if (!miniin.UnpackError())
        {
          hal.drive.Throttle(throttle);
        }
      }
    }

    else if (key == CMD_TURN) {
      if (length == 3)
      {
        float turn = miniin.UnpackFloat();
        if (!miniin.UnpackError())
        {
          hal.drive.Turn(turn);
        }
      }
    }

    else if (key == CMD_SLIDE) {
      if (length == 3)
      {
        float slide = miniin.UnpackFloat();
        if (!miniin.UnpackError())
        {
          hal.drive.Slide(slide);
        }
      }
    }

  } // if hal.GetOn()



}


void HandleComms()
{
  while (SERIAL_BLUE.available())
  {
    byte packet_length = miniin.Give(SERIAL_BLUE.read());
    if (packet_length)
    {
      ProcessComm(packet_length);
    }
  }
}


Periodic update_periodic;

void setup()
{
  hal.Init();

  update_periodic.Init(UPDATE_PERIOD_MS);
}



void loop()
{
  hal.Update();

  HandleComms();

  while (!update_periodic.Elapsed()) {}
}
