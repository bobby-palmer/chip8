#include <fstream>

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
