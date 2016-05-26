#include <vector>
#include "world.hpp"

vector2ui World::size()
{
  if ( map.size() > 0 )
    return vector2ui( map.size(), map[0].size() );
  else
    return vector2ui( map.size(), 0 );
}

void World::size( unsigned int newX, unsigned int newY )
{
  map.resize( newX );
  mapShapes.resize( newX );

  for ( unsigned int x = 0; x < newX; x++ )
  {
    map[x].resize( newY );
    mapShapes[x].resize( newY );

    for ( unsigned int y = 0; y < newY; y++ )
    {
      map[x][y].type = 0;
      mapShapes[x][y].setSize( sf::Vector2f( CHUNK_SIZE, CHUNK_SIZE ) );
      mapShapes[x][y].setPosition( x * CHUNK_SIZE, y * CHUNK_SIZE );
    }
  }
}

void World::size( vector2ui pos )
{
  size( pos.x, pos.y );
}

void World::set( unsigned int x, unsigned int y, int newType )
{
  map[x][y].type = newType;

  if ( newType == LAND )
    mapShapes[x][y].setFillColor( sf::Color::Green );
  else if ( newType == WATER )
    mapShapes[x][y].setFillColor( sf::Color::Blue );
}

void World::set( vector2ui pos, int newType )
{
  set( pos.x, pos.y, newType );
}

int World::getType( unsigned int x, unsigned int y )
{
  return map[x][y].type;
}

int World::getType( vector2ui pos )
{
  return getType( pos.x, pos.y );
}

sf::RectangleShape& World::getShape( unsigned int x, unsigned int y )
{
  return mapShapes[x][y];
}

sf::RectangleShape& World::getShape( vector2ui pos )
{
  return getShape( pos.x, pos.y );
}

std::vector< Chunk > surroundingChunks( World* world, unsigned int x, unsigned int y )
{
  std::vector< Chunk > r;
  Chunk blank;

  if ( x > world->size().x - 1 || y > world->size().y - 1 )
    throw new std::string("surroundingChunks:coords are not in world " + std::to_string(x) + "," + std::to_string(y) + "." );

  if ( x == 0 && y == 0 )
  {
    r.push_back( blank );
    r.push_back( blank );
    r.push_back( blank );
    r.push_back( blank );
    r.push_back( world->map[x+1][y  ] );
    r.push_back( blank );
    r.push_back( world->map[x  ][y+1] );
    r.push_back( world->map[x+1][y+1] );
  }
  else if ( x > 0 && x < world->size().x - 1 && y == 0 )
  {
    r.push_back( blank );
    r.push_back( blank );
    r.push_back( blank );
    r.push_back( world->map[x-1][y  ] );
    r.push_back( world->map[x+1][y  ] );
    r.push_back( world->map[x-1][y+1] );
    r.push_back( world->map[x  ][y+1] );
    r.push_back( world->map[x+1][y+1] );
  }
  else if ( x == world->size().x - 1 && y == 0 )
  {
    r.push_back( blank );
    r.push_back( blank );
    r.push_back( blank );
    r.push_back( world->map[x-1][y  ] );
    r.push_back( blank );
    r.push_back( world->map[x-1][y+1] );
    r.push_back( world->map[x  ][y+1] );
    r.push_back( blank );
  }
  else if ( x == 0 && y > 0 && y < world->size().y - 1 )
  {
    r.push_back( blank );
    r.push_back( world->map[x  ][y-1] );
    r.push_back( world->map[x+1][y-1] );
    r.push_back( blank );
    r.push_back( world->map[x+1][y  ] );
    r.push_back( blank );
    r.push_back( world->map[x  ][y+1] );
    r.push_back( world->map[x+1][y+1] );
  }
  else if ( x > 0 && y > 0 && x < world->size().x - 1 && y < world->size().y - 1 )
  {
    r.push_back( world->map[x-1][y-1] );
    r.push_back( world->map[x  ][y-1] );
    r.push_back( world->map[x+1][y-1] );
    r.push_back( world->map[x-1][y  ] );
    r.push_back( world->map[x+1][y  ] );
    r.push_back( world->map[x-1][y+1] );
    r.push_back( world->map[x  ][y+1] );
    r.push_back( world->map[x+1][y+1] );
  }
  else if ( x == world->size().x - 1 && y > 0 && y < world->size().y - 1 )
  {
    r.push_back( world->map[x-1][y-1] );
    r.push_back( world->map[x  ][y-1] );
    r.push_back( blank );
    r.push_back( world->map[x-1][y  ] );
    r.push_back( blank );
    r.push_back( world->map[x-1][y+1] );
    r.push_back( world->map[x  ][y+1] );
    r.push_back( blank );
  }
  else if ( x == 0 && y == world->size().y - 1 )
  {
    r.push_back( blank );
    r.push_back( world->map[x  ][y-1] );
    r.push_back( world->map[x+1][y-1] );
    r.push_back( blank );
    r.push_back( world->map[x+1][y  ] );
    r.push_back( blank );
    r.push_back( blank );
    r.push_back( blank );
  }
  else if ( x > 0 && x < world->size().x - 1 && y == world->size().x - 1 )
  {
    r.push_back( world->map[x-1][y-1] );
    r.push_back( world->map[x  ][y-1] );
    r.push_back( world->map[x+1][y-1] );
    r.push_back( world->map[x-1][y  ] );
    r.push_back( world->map[x+1][y  ] );
    r.push_back( blank );
    r.push_back( blank );
    r.push_back( blank );
  }
  else if ( x == world->size().x - 1 && y == world->size().x - 1 )
  {
    r.push_back( world->map[x-1][y-1] );
    r.push_back( world->map[x  ][y-1] );
    r.push_back( blank );
    r.push_back( world->map[x-1][y  ] );
    r.push_back( blank );
    r.push_back( blank );
    r.push_back( blank );
    r.push_back( blank );
  }
  else
    throw new std::string("this should never happen; the if statments in world.cpp:surroundingChunks() are incorrect.");

  return r;
}

std::vector< Chunk > surroundingChunks( World* world, vector2ui pos )
{
  return surroundingChunks( world, (unsigned)pos.x, (unsigned)pos.y );
}