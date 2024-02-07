CC=g++
BIN=emulator
SRC=src/*.cpp
FLAGS= -std=c++17

$(BIN):
	$(CC) $(SRC) $(FLAGS) -o $(BIN) -I include -L lib -l SDL2-2.0.0

clean:
	rm -f $(BIN)
