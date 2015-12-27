
#pragma once


#include "Energia.h"


const unsigned int MINIPACKET_MAX_PACKET_LENGTH = 30;

const byte MINIPACK_MESSAGE_START = '(';
const byte MINIPACK_MESSAGE_END = ')';

const byte MINIPACK_MESSAGE_ZERO = '0';
const byte MINIPACK_MESSAGE_BASE = 64;
const byte MINIPACK_CHAR_BITS = 6;

const byte MINIPACK_MAX_CHARS_PER_PACK = 5;


class MinipackInput {
public:
  MinipackInput();
  
  // if a packet is complete: returns the number of chars in the packet
  byte give(char ch);
  
  uint32_t unpack(byte char_count);
  int32_t unpackSigned(byte char_count);
  bool unpackError();
  
private:

  byte chr2bits(char ch);

  bool error; // flag for a read error
  bool started; // flag for if a packet start was detected
  byte index; // the index of _in_packet being written to
  char packet[MINIPACKET_MAX_PACKET_LENGTH]; // Storage for the read packet
};


class MinipackOutput {
public:
  MinipackOutput();

  void newPacket();
  void pack(byte char_count, uint32_t num);
  void packSigned(byte char_count, int32_t num);
  char* endPacket();

private:

  char bits2chr(byte bits);

  byte index; // the index of _in_packet being written to
  char packet[MINIPACKET_MAX_PACKET_LENGTH]; // Storage for the read packet
};









