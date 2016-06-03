#ifndef CHUNK_TYPE
#define CHUNK_TYPE

#include <cmath>
#include <SFML/Graphics.hpp>
#include "../defaults.hpp"

struct Chunk
{
  Chunk()
  {
    shape = sf::CircleShape( CHUNK_DIAMETER / 2, 6 );
    shape.setFillColor( sf::BG_COLOUR );
    shape.setRotation(30);
  }

  int type = 0;
  sf::CircleShape shape;
};

#endif // CHUNK_TYPE
