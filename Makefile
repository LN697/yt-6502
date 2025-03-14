GXX = g++

build:
	$(GXX) -g -o main main_6502.cpp

clean:
	rm -rf main
