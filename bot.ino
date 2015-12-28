
#include "Energia.h"
#include "Servo.h"

#include "common.h"
#include "vmap.h"
#include "timer.h"
#include "hal.h"
#include "minipack.h"

#include "cmd_keys.h"


MinipackInput miniin;
MinipackOutput miniout;


void process_comm(byte length)
{

  byte key = miniin.unpack(1);

  if (key == CMD_ACK) if (length == 1)
  {

    if (!miniin.unpackError())
    {
      miniout.newPacket();
      miniout.pack(1, RESPONSE_ACK);
      SERIAL_BLUE.write(miniout.endPacket());
    }
  }

  else if (key == CMD_ENABLE) if (length == 2)
  {
    byte enable_state = miniin.unpack(1);
    if (!miniin.unpackError())
    {
      hal.set_on(enable_state);
    }
  }

  else if (key == CMD_STATUS) if (length == 1)
  {
    if (!miniin.unpackError())
    {
      byte status =
        (hal.error() << RESPONSE_STATUS_BIT_ERROR) ||
        (hal.get_on() << RESPONSE_STATUS_BIT_MASTER_ON) ||
        (hal.armed() << RESPONSE_STATUS_BIT_ARMED);


      miniout.newPacket();
      miniout.pack(1, status);
      SERIAL_BLUE.write( miniout.endPacket() );
    }
  }

  else if (hal.get_on())
  { // commands past this point require master on   
  
  if (key == CMD_ARM) if (length == 2)
  {
    byte arm_cmd = miniin.unpack(1);
    if (!miniin.unpackError())
    {
      if (arm_cmd == CMD_ARM_OPEN)
      {
        hal.arm();
      }
      else if (arm_cmd == CMD_ARM_MAINTAIN)
      {
        hal.maintain_arm();
      }
      else if (arm_cmd == CMD_ARM_CLOSE)
      {
        hal.disarm();
      }
    }
  }

  if (key == CMD_THROTTLE) if (length == 3)
  {
    short throttle = miniin.unpackSigned(2);
    if (!miniin.unpackError())
    {
      hal.drive.throttle(throttle / 1000.0);
    }
  }

  if (key == CMD_TURN) if (length == 3)
  {
    short turn = miniin.unpackSigned(2);
    if (!miniin.unpackError())
    {
      hal.drive.turn(turn / 1000.0);
    }
  }

  if (key == CMD_SLIDE) if (length == 3)
  {
    short slide = miniin.unpackSigned(2);
    if (!miniin.unpackError())
    {
      hal.drive.slide(slide / 1000.0);
    }
  }

  } // if hal.get_on()



}


void handle_comms()
{
  while (SERIAL_BLUE.available())
  {
    byte packet_length = miniin.give(SERIAL_BLUE.read());
    if (packet_length)
    {
      process_comm(packet_length);
    }
  }
}


Periodic update_periodic;

void setup()
{
  hal.init();

  update_periodic.init(UPDATE_PERIOD_MS);
}



void loop()
{
  hal.update();

  handle_comms();

  while (!update_periodic.elapsed()) {}
}
