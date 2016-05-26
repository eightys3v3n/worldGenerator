#ifndef GENERATOR_
#define GENERATOR_

#include <thread>
#include <future>
#include "world.hpp"

typedef sf::Vector2<unsigned int> vector2ui;

struct ChunkQueue
{
  vector2ui pos;
  std::promise< int > p;
  std::future< int > f = p.get_future();
  std::vector< std::future< int >* > r;
};

void generateChunk( World* world, vector2ui pos );
void generateChunkAsync( int l, int c, World* world, ChunkQueue* chunk );
void generate( World* world );

#endif // GENERATOR_