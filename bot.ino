
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


void process_comm(byte packet_length)
{
  byte key = miniin.unpack(1);

  if (key == CMD_ACK)
  {
    miniout.newPacket();
    miniout.pack(1, RESPONSE_ACK);
    SERIAL_BLUE.write(  miniout.endPacket() );
  }
  if (key == CMD_ENABLE)
  {

  }
}

bool red = false;

void handle_comms()
{
  while (SERIAL_BLUE.available())
  {

    red = !red;
    digitalWrite(PIN_LED_RED, red);

    byte packet_length = miniin.give(SERIAL_BLUE.read());
    if (packet_length > 2)  // 2 chars is only "()"
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
