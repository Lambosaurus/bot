
#include "minipack.h"



MinipackInput::MinipackInput()
{
  error = false;
  started = false;
}


byte MinipackInput::give(char ch)
{
  if ( ch == MINIPACK_MESSAGE_START )
  {
    // new message, start filling buffer
    packet[0] = ch;
    started = true;
    index = 1;
    error = false; // Important to note we clear the error flag here.
  }
  
  else if (started) // if we already have a packet to fill
  {
    if (index == MINIPACKET_MAX_PACKET_LENGTH)
    {
      // buffer overflow inbound... ABORT!
      started = false;
      index = 0;
    }
    else
    {
      packet[index++] = ch; // Load 'er up!
      
      if (ch == MINIPACK_MESSAGE_END) // check for termination
      {
        packet[index] = 0; // null terminate for good measure.
        started = false;
        
        byte index_copy = index;
        index = 1;
        return index_copy;
      }
    }
  }
  return 0;
}

byte MinipackInput::chr2bits(char ch)
{
  byte bits = ch - MINIPACK_MESSAGE_ZERO;
  error |= (bits >= MINIPACK_MESSAGE_BASE);
  return bits;
}

uint32_t MinipackInput::unpack(byte char_count)
{
  if (error) { return 0; } // if there is a logged error, then dont waste any time
  
  uint32_t num = 0;
  for ( byte i = 0; i < char_count; i++ )
  {
    // for each char, we read it, then decode it
    byte bits = chr2bits(packet[index + i]);
    
    num <<= MINIPACK_CHAR_BITS;
    num += bits;
  }
  index += char_count;
  return num;
}

int32_t MinipackInput::unpackSigned(byte char_count)
{
  uint32_t halfway = 1 << ((char_count*MINIPACK_CHAR_BITS) - 1);

  return unpack(char_count) - halfway; 
}

bool MinipackInput::unpackError()
{
  return ( (!error) && (packet[index] == MINIPACK_MESSAGE_END) );
}





MinipackOutput::MinipackOutput()
{
  index = 1;
  packet[0] = MINIPACK_MESSAGE_START;
  packet[1] = 0;
}


void MinipackOutput::newPacket()
{
  index = 1;
}

void MinipackOutput::pack(byte char_count, uint32_t num)
{
  byte end_index = index + char_count - 1;
  for (byte i = 0; i < char_count; i++)
  {
    byte bits = num & ((1 << MINIPACK_CHAR_BITS) - 1);
    packet[end_index - i] = bits2chr(bits);
    num >>= MINIPACK_CHAR_BITS;
  }
  index += char_count;
}

void MinipackOutput::packSigned(byte char_count, int32_t num)
{
  uint32_t halfway = (char_count*MINIPACK_CHAR_BITS) - 1;
  pack(char_count, halfway + num);
}

char* MinipackOutput::endPacket()
{
  packet[index] = MINIPACK_MESSAGE_END;
  packet[index + 1] = 0;

  return packet;
}


char MinipackOutput::bits2chr(byte bits)
{
  return bits + MINIPACK_MESSAGE_ZERO;
}














