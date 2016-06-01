#ifndef CHUNK_TYPE
#define CHUNK_TYPE

#include <SFML/Graphics.hpp>
#include "../defaults.hpp"

struct Chunk
{
  Chunk()
  {
    shape.setFillColor( sf::BG_COLOUR );
    shape.setSize( sf::Vector2f{ CHUNK_SIZE, CHUNK_SIZE } );
    shape.setPoint( 0, sf::Vector2f{ -.5 * 1/3 * CHUNK_SIZE , -.5 * CHUNK_SIZE } );
    shape.setPoint( 0, sf::Vector2f{ +.5 * 1/3 * CHUNK_SIZE , -.5 * CHUNK_SIZE } );
    shape.setPoint( 0, sf::Vector2f{ +.5 * CHUNK_SIZE , 0 } );
    shape.setPoint( 0, sf::Vector2f{ +.5 * 1/3 * CHUNK_SIZE , +.5 * CHUNK_SIZE } );
    shape.setPoint( 0, sf::Vector2f{ -.5 * 1/3 * CHUNK_SIZE , +.5 * CHUNK_SIZE } );
    shape.setPoint( 0, sf::Vector2f{ -.5 * CHUNK_SIZE , 0 } );
    shape.setPoint( 0, sf::Vector2f{ -.5 * 1/3 * CHUNK_SIZE , -.5 * CHUNK_SIZE } );
  }

  int type = 0;
  sf::ConvexShape shape;
};

#endif // CHUNK_TYPE
