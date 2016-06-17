#ifndef CHUNK_TYPE
#define CHUNK_TYPE

#include <cmath>
#include <SFML/Graphics.hpp>
#include "../defaults.hpp"

struct Chunk
{
  Chunk()
  {
    shape.setFillColor( sf::BG_COLOUR );
    shape.setSize( sf::Vector2f{ CHUNK_SIZE, CHUNK_SIZE } );
    shape.setPosition(0,0);
      shape.setOrigin( CHUNK_SIZE / 2, CHUNK_SIZE / 2);
  }

  int type = 0;
  sf::RectangleShape shape;
};

#endif // CHUNK_TYPE
