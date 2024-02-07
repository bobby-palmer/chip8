#pragma once

#include "types.h"

const unsigned int ROM_START = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;
const unsigned int VIDEO_WIDTH = 64;
const unsigned int VIDEO_HEIGHT = 32;

class chip8 {
public:
  byte r[16];
  byte memory[4096];
  address index;
  address pc;
  address stack[16];
  byte sp;
  byte delay_timer;
  byte sound_timer;
  byte keypad[16];
  uint32_t video[VIDEO_WIDTH * VIDEO_HEIGHT];
  address opcode;

  void init();
  void load_rom(char const* filename);
  void cycle();
  void load_op();

  byte random_byte();

  void run_op0();
  void run_op8();
  void run_opE();
  void run_opF();

  // opcodes
  void OP_NULL();
  void OP_00E0();
  void OP_00EE();
  void OP_0nnn();
  void OP_1nnn();
  void OP_2nnn();
  void OP_3xkk();
  void OP_4xkk();
  void OP_5xy0();
  void OP_6xkk();
  void OP_7xkk();
  void OP_8xy0();
  void OP_8xy1();
  void OP_8xy2();
  void OP_8xy3();
  void OP_8xy4();
  void OP_8xy5();
  void OP_8xy6();
  void OP_8xy7();
  void OP_8xyE();
  void OP_9xy0();
  void OP_Annn();
  void OP_Bnnn();
  void OP_Cxkk();
  void OP_Dxyn();
  void OP_Ex9E();
  void OP_ExA1();
  void OP_Fx07();
  void OP_Fx0A();
  void OP_Fx15();
  void OP_Fx18();
  void OP_Fx1E();
  void OP_Fx29();
  void OP_Fx33();
  void OP_Fx55();
  void OP_Fx65();
};
