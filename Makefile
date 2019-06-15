gcc=g++
args=--std=c++17 -Wall -Wextra
part=$(gcc) $(args) -c
full=$(gcc) $(args)

all: main

main: build/main.o build/world.o build/generator.o build/draw.o build/input.o build/entity.type.o build/heightMap.type.o
	$(full) -lsfml-graphics -lsfml-window -lsfml-system -lpthread -g build/* -o main

build/main.o: main.cpp defaults.hpp data_types/queue.cpp data_types/queue.hpp
	$(part) main.cpp -o build/main

build/world.o: world.cpp world.hpp data_types/chunk.cpp defaults.hpp data_types/queue.cpp data_types/queue.hpp
	$(part) world.cpp -o build/world.o

build/generator.o: generator.cpp world.hpp defaults.hpp data_types/queue.cpp data_types/queue.hpp
	$(part) generator.cpp -o build/generator.o

build/window.o: window.cpp defaults.hpp data_types/queue.cpp data_types/queue.hpp
	$(part) window.cpp -o build/window.o

build/draw.o: draw.cpp draw.hpp
	$(part) draw.cpp -o build/draw.o

build/input.o: input.cpp input.hpp data_types/entity.hpp world.hpp
	$(part) input.cpp -o build/input.o

build/entity.type.o: data_types/entity.cpp data_types/entity.hpp
	$(part) data_types/entity.cpp -o build/entity.type.o

build/heightMap.type.o: data_types/heightMap.cpp data_types/heightMap.hpp
	$(part) data_types/heightMap.cpp -o build/heightMap.type.o

clean:
	rm build/*
