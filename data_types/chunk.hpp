#ifndef CHUNK_TYPE
#define CHUNK_TYPE

#include <SFML/Graphics.hpp>

struct Chunk
{
  int type = 0;
  sf::RectangleShape shape;
};

#endif // CHUNK_TYPE