gcc=g++
args=--std=c++17 -Wall -Wextra -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lpthread -g
part=$(gcc) $(args) -c
full=$(gcc) $(args)
library=tmp/world.main.o tmp/generator.main.o tmp/window.main.o

all: main test

main: tmp/main $(library)
	$(full) tmp/main tmp/*.main.o -o main

tmp/main: main.cpp
	$(part) main.cpp -o tmp/main

tmp/world.main.o: world.cpp world.hpp chunk.hpp
	$(part) world.cpp -o tmp/world.main.o

tmp/generator.main.o: generator.cpp world.hpp
	$(part) generator.cpp -o tmp/generator.main.o

tmp/window.main.o: window.cpp
	$(part) window.cpp -o tmp/window.main.o

test: tmp/test $(library) tmp/world.test.o
	$(full) tmp/test tmp/*.main.o tmp/*.test.o -o test

tmp/test: main_test.cpp world.hpp
	$(part) main_test.cpp -o tmp/test

tmp/world.test.o: world_test.cpp world.hpp
	$(part) world_test.cpp -o tmp/world.test.o

clean:
	if [[ -n tmp/* ]]; then rm tmp/*; fi