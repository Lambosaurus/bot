#pragma once




enum CMD_KEYS {
  CMD_STOP = 0, //
  CMD_ACK,      //
  CMD_ENABLE,   // 1u
  CMD_CONNECT, // 1u
  CMD_STATUS, //
  
  // master on should be enabled for commands below
  CMD_THROTTLE, // 2s
  CMD_TURN, // 2s
  CMD_SLIDE, // 2s
};



enum CMD_ARM_COMMANDS {
  CMD_ARM_OPEN,
  CMD_ARM_MAINTAIN,
  CMD_ARM_CLOSE,
};

enum RESPONSE_KEYS {
  RESPONSE_ACK,
  RESPONSE_STATUS,
};

enum RESPONSE_STATUS {
  RESPONSE_BIT_ERROR,
  RESPONSE_BIT_MASTER_ON,
  RESPONSE_BIT_DRIVE_ENABLED,
};




