#ifndef WORLD_TEST
#define WORLD_TEST

#include <vector>
#include "chunk.hpp"
#include "world.hpp"

namespace test
{
  void printChunks( std::vector< Chunk > chunks );
  void surroundingChunks( World& world );
}

#endif // WORLD_TEST