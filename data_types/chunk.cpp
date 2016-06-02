#ifndef CHUNK_TYPE
#define CHUNK_TYPE

#include <SFML/Graphics.hpp>
//#include "../defaults.hpp"

struct Chunk
{
  Chunk()
  {
    shape = sf::CircleShape( CHUNK_SIZE / 2, 6 );
    shape.setFillColor( sf::BG_COLOUR );
  }

  int type = 0;
  sf::CircleShape shape;
};

#endif // CHUNK_TYPE
