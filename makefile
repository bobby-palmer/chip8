emu:
	g++ src/*.cpp -std=c++17 -o emulator -I include -L lib -l SDL2-2.0.0
clean:
	rm emulator
