gcc=g++
args=--std=c++17 -Wall -Wextra
part=$(gcc) $(args) -c
full=$(gcc) $(args)

all: main

main: tmp/main tmp/world.o tmp/generator.o tmp/draw.o tmp/input.o tmp/entity.type.o tmp/heightMap.type.o
	$(full) -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lpthread -g tmp/* -o main

tmp/main: main.cpp defaults.hpp data_types/queue.cpp data_types/queue.hpp
	$(part) main.cpp -o tmp/main

tmp/world.o: world.cpp world.hpp data_types/chunk.cpp defaults.hpp data_types/queue.cpp data_types/queue.hpp
	$(part) world.cpp -o tmp/world.o

tmp/generator.o: generator.cpp world.hpp defaults.hpp data_types/queue.cpp data_types/queue.hpp
	$(part) generator.cpp -o tmp/generator.o

tmp/window.o: window.cpp defaults.hpp data_types/queue.cpp data_types/queue.hpp
	$(part) window.cpp -o tmp/window.o

tmp/draw.o: draw.cpp draw.hpp
	$(part) draw.cpp -o tmp/draw.o

tmp/input.o: input.cpp input.hpp data_types/entity.hpp world.hpp
	$(part) input.cpp -o tmp/input.o

tmp/entity.type.o: data_types/entity.cpp data_types/entity.hpp
	$(part) data_types/entity.cpp -o tmp/entity.type.o

tmp/heightMap.type.o: data_types/heightMap.cpp data_types/heightMap.hpp
	$(part) data_types/heightMap.cpp -o tmp/heightMap.type.o

clean:
	rm tmp/*