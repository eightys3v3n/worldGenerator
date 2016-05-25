#ifndef GENERATOR_
#define GENERATOR_

#include <thread>
#include "world.hpp"

typedef sf::Vector2<unsigned int> vector2ui;

void generateChunk( World& world, unsigned int x, unsigned int y );
void generateChunk( World& world, vector2ui pos );
std::thread generateChunkAsync( World& world, unsigned int x, unsigned int y );
std::thread generateChunkAsync( World& world, vector2ui pos );
void generate( World& world );

#endif // GENERATOR_