all: histogram clean

basic_sdl.o: lib/basic_sdl.hh lib/basic_sdl.cc
	g++ -c lib/basic_sdl.cc

equalize.o: lib/equalize.hh lib/equalize.cc
	g++ -c lib/equalize.cc

button.o: lib/button.hh lib/button.cc
	g++ -c lib/button.cc

main.o: src/main.cc
	g++ -c src/main.cc

histogram: basic_sdl.o equalize.o button.o main.o
	g++ -o histogram basic_sdl.o equalize.o button.o main.o -lSDL -lSDL_image -lSDL_ttf -lm

clean:
	rm -rf *.o
