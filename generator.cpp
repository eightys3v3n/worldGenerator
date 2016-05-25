#include <vector>
#include <SFML/System.hpp>
#include "world.hpp"

typedef sf::Vector2<unsigned int> vector2ui;
typedef sf::Vector2<double> vector2d;


void generateChunk( World& world, unsigned int x, unsigned int y )
{
  int type = 0;
  int r;
  vector2d land, water;
  std::vector< Chunk > chunks;

  land = LAND_PROB;
  water = WATER_PROB;

  chunks = surroundingChunks( world, x, y );

  for ( unsigned int c = 0; c < chunks.size(); c++ )
  {
    if ( chunks[c].type == LAND )
    {
      land.y += 5;
      water.x += 5;
    }
    else if ( chunks[c].type == WATER )
    {
      land.y -= 5;
      water.y -= 5;
    }
  }

  r = rand() % 100;

  if ( r >= land.x && r <= land.y )
    type = LAND;
  else if ( r >= water.x && r <= water.y )
    type = WATER;

  world.set( x, y, type );
}

void generateChunk( World& world, vector2ui pos )
{
  generateChunk( world, pos.x, pos.y );
}

void generate( World& world )
{
  unsigned int x = world.size().x / 2;
  unsigned int y = world.size().y / 2;
  generateChunk( world, x,y );

  for ( unsigned int r = 0; r < VIEW_DISTANCE; r++ )
  {
    generateChunk( world, x + r, y );
    generateChunk( world, x - r, y );
  }
}