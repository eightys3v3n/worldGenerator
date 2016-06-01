#include <vector>
#include <map>
#include "defaults.hpp"
#include "world.hpp"


void World::init( long long x, long long y )
{
  data[x][y].type = 0;
}

bool World::exists( long long x, long long y )
{
  if ( data.find(x) != data.end() )
    if ( data[x].find(y) != data[x].end() )
      return true;

  return false;
}

long long World::size()
{
  return data.size();
}

void World::set( long long x, long long y, int t )
{
  if ( data[x][y].type == 0 )
    init(x,y);

  data[x][y].type = t;

  if ( t == LAND )
    data[x][y].shape.setFillColor( sf::Color::Green );
  else if ( t == WATER )
    data[x][y].shape.setFillColor( sf::Color::Blue );
}

void World::set( vector2ll pos, int t )
{
  set( pos.x, pos.y, t );
}

Chunk* World::get( long long x, long long y )
{
  return &data[x][y];
}

Chunk* World::get( vector2ll pos )
{
  return get( pos.x, pos.y );
}

sf::RectangleShape& World::shape( long long x, long long y )
{
  return data[x][y].shape;
}

sf::RectangleShape& World::shape( vector2ll pos )
{
  return shape( pos.x, pos.y );
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

std::vector< Chunk* > surroundingChunks( World* world, vector2ll pos )
{
  return surroundingChunks( world, pos.x, pos.y );
}
