COMPILER = gcc
SRC = quantizer.c compressor.c decompressor.c
BIN = ejecutable
COMMANDS = clear
FLAGS = -lm -o

all: build clear	run clean

clear:
	$(COMMANDS)
build:
	$(COMPILER) $(FLAGS) $(BIN) $(SRC)
run:
	./$(BIN)
clean:
	rm $(BIN)
