#include <fstream>
#include <iterator>

#include "chip8.h"
#include "fontset.h"

const unsigned int ROM_START = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;

void chip8::init() {
  pc = ROM_START;
  load_fonts(memory + FONTSET_START_ADDRESS);
}

void chip8::load_rom(char const* filename) 
{
	// Open the file as a stream of binary and move the file pointer to the end
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (file.is_open())
	{
		// Get size of file and allocate a buffer to hold the contents
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		// Go back to the beginning of the file and fill the buffer
		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		// Load the ROM contents into the Chip8's memory, starting at 0x200
		for (long i = 0; i < size; ++i)
		{
			memory[ROM_START + i] = buffer[i];
		}

		// Free the buffer
		delete[] buffer;
	}
};

void chip8::OP_00E0() {
  memset(video, 0, sizeof(video));
};

void chip8::OP_00EE() {
  --sp;
  pc = stack[sp];
};

void chip8::OP_1nnn() {
  address a = opcode & 0x0FFFu;
  pc = a;
};

void chip8::OP_2nnn() {
  address a = opcode & 0x0FFFu;

  stack[sp] = pc;
  ++sp;
  pc = a;
};

void chip8::OP_3xkk() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte b = opcode & 0x00FFu;

  if (r[Vx] == b) 
    pc += 2;
};

void chip8::OP_4xkk() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte b = opcode & 0x00FFu;

  if (r[Vx] != b) 
    pc += 2;
};

void chip8::OP_5xy0() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
	byte Vy = (opcode & 0x00F0u) >> 4u;

	if (r[Vx] == r[Vy])
		pc += 2;
};

void chip8::OP_6xkk() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte b  = opcode & 0x00FFu;

  r[Vx] = b;
};

void chip8::OP_7xkk() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte b = opcode & 0x00FFu;

  r[Vx] += b;
};

void chip8::OP_8xy0() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte Vy = (opcode & 0x00F0u) >> 4u;

  r[Vx] = r[Vy];
};

void chip8::OP_8xy1() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte Vy = (opcode & 0x00F0u) >> 4u;

  r[Vx] |= r[Vy];
};

void chip8::OP_8xy2() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte Vy = (opcode & 0x00F0u) >> 4u;

  r[Vx] &= r[Vy];
};

void chip8::OP_8xy3() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte Vy = (opcode & 0x00F0u) >> 4u;

  r[Vx] ^= r[Vy];
};

void chip8::OP_8xy4() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte Vy = (opcode & 0x00F0u) >> 4u;

  uint16_t sum = r[Vx] + r[Vy];
  if (sum > 255U) r[0xF] = 1;
  else            r[0xF] = 0;

  r[Vx] = sum & 0xFFu;
};

void chip8::OP_8xy5() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte Vy = (opcode & 0x00F0u) >> 4u;

  if (r[Vx] > r[Vy]) r[0xF] = 1;
  else               r[0xF] = 0;

  r[Vx] -= r[Vy];
};

void chip8::OP_8xy6() {
  byte Vx = (opcode & 0x0F00u) >> 8u;

  r[0xF] = (r[Vx] & 0x1u);

  r[Vx] >>= 1;
};

void chip8::OP_8xy7() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte Vy = (opcode & 0x00F0u) >> 4u;

  r[0xF] = (r[Vy] > r[Vx]);

  r[Vx] = r[Vy] - r[Vx];
};

void chip8::OP_8xyE() {
  byte Vx = (opcode & 0x0F00u) >> 8u;

  r[0xF] = (r[Vx] & 0x80u) >> 7u;

  r[Vx] <<= 1;
};

void chip8::OP_9xy0() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte Vy = (opcode & 0x00F0u) >> 4u;

  if (r[Vx] != r[Vy]) pc += 2;
};

void chip8::OP_Annn() {
  address a = opcode & 0x0FFFu;

  index = a;
};

void chip8::OP_Bnnn() {
  address a = opcode & 0x0FFFu;

  pc = r[0] + a;
};

void chip8::OP_Cxkk() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte b = opcode & 0x00FFu;

  r[Vx] = byte & //RANDOM BYTE
};

void chip8::OP_Dxyn() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte Vy = (opcode & 0x00F0u) >> 4u;
  byte height = opcode & 0x000Fu;

  byte xPos = r[Vx] % VIDEO_WIDTH;
  byte yPos = r[Vy] % VIDEO_HEIGHT;

  r[0xF] = 0;

  for (unsigned int row = 0; row < height; ++row)
	{
		uint8_t spriteByte = memory[index + row];

		for (unsigned int col = 0; col < 8; ++col)
		{
			uint8_t spritePixel = spriteByte & (0x80u >> col);
			uint32_t* screenPixel = &video[(yPos + row) * VIDEO_WIDTH + (xPos + col)];

			// Sprite pixel is on
			if (spritePixel)
			{
				// Screen pixel also on - collision
				if (*screenPixel == 0xFFFFFFFF)
				{
					r[0xF] = 1;
				}

				// Effectively XOR with the sprite pixel
				*screenPixel ^= 0xFFFFFFFF;
			}
		}
	}
};

void chip8::OP_Ex9E() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte key = r[Vx];

  if (keypad[key]) pc += 2;
};

void chip8::OP_ExA1() {
  byte Vx = (opcode & 0x0F00u) >> 8u;

  byte key = r[Vx];

  if (!keypad[key]) pc += 2;
};

void chip8::OP_Fx07() {
  byte Vx = (opcode & 0x0F00u) >> 8u;

  r[Vx] = delay_timer;
};

void chip8::OP_Fx0A() {
  byte Vx = (opcode & 0x0F00u) >> 8u;

  for (int i = 0; i < 16; ++i) {
    if (keypad[i]) {
      r[Vx] = i;
      return;
    }
  }
  pc -= 2;
};

void chip8::OP_Fx15() {
  byte Vx = (opcode & 0x0F00u) >> 8u;

  delay_timer = r[Vx];
};

void chip8::OP_Fx18() {
  byte Vx = (opcode & 0x0F00u) >> 8u;

  sound_timer = r[Vx];
};

void chip8::OP_Fx1E() {
  byte Vx = (opcode & 0x0F00u) >> 8u;

  index += r[Vx];
};

void chip8::OP_Fx29() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte digit = r[Vx];

  index = FONTSET_START_ADDRESS + (5 * digit);
};

void chip8::OP_Fx33() {
  byte Vx = (opcode & 0x0F00u) >> 8u;
  byte value = r[Vx];

  memory[index + 2] = value % 10;
  value /= 10;

  memory[index + 1] = value % 10;
  value /= 10;

  memory[index] = value % 10;
};

void chip8::OP_Fx55() {
  byte Vx = (opcode & 0x0F00u) >> 8u;

  for (byte i = 0; i <= Vx; ++i) {
    r[i] = memory[index + i];
  }
}
