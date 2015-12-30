
#pragma once


#include "Energia.h"


const unsigned int MINIPACKET_MAX_PACKET_LENGTH = 30;

const byte MINIPACK_MESSAGE_START = '(';
const byte MINIPACK_MESSAGE_END = ')';

const byte MINIPACK_MESSAGE_ZERO = '0';
const byte MINIPACK_MESSAGE_BASE = 64;
const byte MINIPACK_CHAR_BITS = 6;

const byte MINIPACK_MAX_CHARS_PER_PACK = 5;



const byte MINIPACK_FLOAT_CHARS = 3;
const byte MINIPACK_FLOAT_SCALAR_BITS = 3;
const byte MINIPACK_FLOAT_SIGN_BITS = 1;
const byte MINIPACK_FLOAT_MANTISSA_BITS = (MINIPACK_CHAR_BITS * MINIPACK_FLOAT_CHARS) - MINIPACK_FLOAT_SCALAR_BITS - MINIPACK_FLOAT_SIGN_BITS;

const unsigned int MINIPACK_FLOAT_MAX_MANTISSA = (1 << MINIPACK_FLOAT_MANTISSA_BITS) - 1;
const unsigned int MINIPACK_FLOAT_MAX_SCALAR = (1 << MINIPACK_FLOAT_SCALAR_BITS)-1;

const float MINIPACK_FLOAT_SCALAR_TABLE[MINIPACK_FLOAT_MAX_SCALAR+1] = {
  0.1,
  1,
  10,
  100,
  1000,
  10000,
  100000,
  1000000,
};


class MinipackInput {
public:
  MinipackInput();
  
  // if a packet is complete: returns the number of chars in the packet
  byte Give(char ch);
  
  uint32_t Unpack(byte char_count);
  int32_t UnpackSigned(byte char_count);
  float UnpackFloat();
  bool UnpackError();
  
private:

  byte Chr2Bits(char ch);

  bool error; // flag for a read error
  bool started; // flag for if a packet start was detected
  byte index; // the index of _in_packet being written to
  char packet[MINIPACKET_MAX_PACKET_LENGTH]; // Storage for the read packet
};


class MinipackOutput {
public:
  MinipackOutput();

  void NewPacket();
  void Pack(byte char_count, uint32_t num);
  void PackSigned(byte char_count, int32_t num);
  void PackFloat(float num);
  char* EndPacket();

private:

  char Bits2Chr(byte bits);

  byte index; // the index of _in_packet being written to
  char packet[MINIPACKET_MAX_PACKET_LENGTH]; // Storage for the read packet
};









