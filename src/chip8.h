#pragma once

#include "types.h"

#include <chrono>
#include <random>

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
  uint32_t video[64 * 32];
  address opcode;

  void init();
  void load_rom(char const* filename);

  // opcodes
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
