
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


void ProcessComm(byte length)
{

  byte key = miniin.Unpack(1);

  if (key == CMD_ACK && length == 1)
  {

    if (!miniin.UnpackError())
    {
      miniout.NewPacket();
      miniout.Pack(1, RESPONSE_ACK);
      SERIAL_BLUE.write(miniout.EndPacket());
    }
  }

  else if (key == CMD_ENABLE && length == 2)
  {
    byte enable_state = miniin.Unpack(1);
    if (!miniin.UnpackError())
    {
      hal.SetOn(enable_state);
    }
  }

  else if (key == CMD_STATUS && length == 1)
  {
    if (!miniin.UnpackError())
    {
      byte status =
        (hal.Error() << RESPONSE_STATUS_BIT_ERROR) |
        (hal.GetOn() << RESPONSE_STATUS_BIT_MASTER_ON) |
        (hal.Armed() << RESPONSE_STATUS_BIT_ARMED);


      miniout.NewPacket();
      miniout.Pack(1, RESPONSE_STATUS);
      miniout.Pack(1, status);
      SERIAL_BLUE.write( miniout.EndPacket() );
    }
  }

  else if (hal.GetOn())
  { // commands past this point require master on   
  
  if (key == CMD_ARM && length == 2)
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

  if (key == CMD_THROTTLE && length == 3)
  {
    short throttle = miniin.UnpackSigned(2);
    if (!miniin.UnpackError())
    {
      hal.drive.Throttle(throttle / 1000.0);
    }
  }

  if (key == CMD_TURN && length == 3)
  {
    short turn = miniin.UnpackSigned(2);
    if (!miniin.UnpackError())
    {
      hal.drive.Turn(turn / 1000.0);
    }
  }

  if (key == CMD_SLIDE && length == 3)
  {
    short slide = miniin.UnpackSigned(2);
    if (!miniin.UnpackError())
    {
      hal.drive.Slide(slide / 1000.0);
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
