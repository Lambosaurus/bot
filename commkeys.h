#pragma once





enum CMD_KEYS {
  CMD_ACK,      //
  CMD_ENABLE,   // 1u
  CMD_STATUS, //

  CMD_GET_ERRS, //
  CMD_CLEAR_ERRS, // -
  CMD_SOFT_ERR, // 1u

  CMD_GET_POWER, //
  
  CMD_CHIRP, // 1u

  // master on should be enabled for commands below
  CMD_ARM, // 1u
  CMD_THROTTLE, // f
  CMD_TURN, // f
  CMD_SLIDE, // f
};



// power reply should be 2u voltage, 2u current


enum CMD_ARM_COMMANDS {
  CMD_ARM_OPEN,
  CMD_ARM_MAINTAIN,
  CMD_ARM_CLOSE,
};

enum RESPONSE_KEYS {
  RESPONSE_ACK,
  RESPONSE_STATUS, // 1u
  RESPONSE_GET_POWER, // f f
};

enum RESPONSE_STATUS {
  RESPONSE_STATUS_BIT_ERROR,
  RESPONSE_STATUS_BIT_MASTER_ON,
  RESPONSE_STATUS_BIT_ARMED,
  RESPONSE_STATUS_BIT_LOW_VOLTAGE,
};




