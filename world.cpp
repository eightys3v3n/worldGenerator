#include <vector>
#include <map>
#include "defaults.hpp"
#include "world.hpp"
#include "data_types/heightMap.hpp"

void World::init( long long x, long long y )
{
  chunkData[x][y].type = 0;
}

bool World::exists( long long x, long long y )
{
  if ( chunkData.find(x) != chunkData.end() )
    if ( chunkData[x].find(y) != chunkData[x].end() )
      return true;

  return false;
}

long long World::size()
{
  return chunkData.size();
}

void World::set( long long x, long long y, int t )
{
  if ( chunkData[x][y].type == 0 )
    init(x,y);

  chunkData[x][y].type = t;

  if ( t == LAND )
    chunkData[x][y].shape.setFillColor( sf::Color::Green );
  else if ( t == WATER )
    chunkData[x][y].shape.setFillColor( sf::Color::Blue );
}

Chunk* World::get( long long x, long long y )
{
  return &chunkData[x][y];
}

HEIGHT_TYPE World::getHeight( long long x, long long y )
{
  return heightData.height(x,y);
}

sf::CircleShape& World::shape( long long x, long long y )
{
  return chunkData[x][y].shape;
}

std::vector< Chunk* > surroundingChunks( World* world, long long x, long long y )
{
  std::vector< Chunk* > r;
  Chunk blank;

  r.push_back( world->get(x-1,y-1) );
  r.push_back( world->get(x  ,y-1) );
  r.push_back( world->get(x+1,y-1) );
  r.push_back( world->get(x-1,y  ) );
  r.push_back( world->get(x+1,y  ) );
  r.push_back( world->get(x-1,y+1) );
  r.push_back( world->get(x  ,y+1) );
  r.push_back( world->get(x+1,y+1) );

  return r;
}