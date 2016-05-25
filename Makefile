gcc=g++
args=--std=c++17 -Wall -Wextra -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -g
part=$(gcc) $(args) -c
full=$(gcc) $(args)

all: main

main: tmp/main tmp/world.o tmp/generator.o tmp/window.o
	$(full) tmp/main tmp/*.o -o main

tmp/main: main.cpp
	$(part) main.cpp -o tmp/main

tmp/world.o: world.cpp world.hpp chunk.hpp
	$(part) world.cpp -o tmp/world.o

tmp/generator.o: generator.cpp world.hpp
	$(part) generator.cpp -o tmp/generator.o

tmp/window.o: window.cpp
	$(part) window.cpp -o tmp/window.o

clean:
	if [[ -n tmp/* ]]; then rm tmp/*; fi