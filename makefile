emu:
	g++ src/main.cpp src/chip8.cpp -o emulator -I include -L lib -l SDL2-2.0.0
clean:
	rm emulator
