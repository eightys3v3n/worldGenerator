#include <vector>
#include "world.hpp"

vector2i World::size()
{
  if ( map.size() > 0 )
    return vector2i( map.size(), map[0].size() );
  else
    return vector2i( map.size(), 0 );
}

void World::size( vector2i pos )
{
  size( pos.x, pos.y );
}

void World::size( int newX, int newY )
{
  map.resize( newX );
  mapShapes.resize( newX );

  for ( int x = 0; x < newX; x++ )
  {
    map[x].resize( newY );
    mapShapes[x].resize( newY );

    for ( int y = 0; y < newY; y++ )
    {
      map[x][y].type = 0;
      mapShapes[x][y].setSize( sf::Vector2f( CHUNK_SIZE, CHUNK_SIZE ) );
      mapShapes[x][y].setPosition( x * CHUNK_SIZE, y * CHUNK_SIZE );
    }
  }
}

void World::set( vector2i pos, int newType )
{
  set( pos.x, pos.y, newType );
}

void World::set( int x, int y, int newType )
{
  map[x][y].type = newType;

  if ( newType == GREEN )
    mapShapes[x][y].setFillColor( sf::Color::Green );
  else if ( newType == BLUE )
    mapShapes[x][y].setFillColor( sf::Color::Blue );
}

int World::getType( vector2i pos )
{
  return getType( pos.x, pos.y );
}

int World::getType( int x, int y )
{
  return map[x][y].type;
}

sf::RectangleShape& World::getShape( vector2i pos )
{
  return getShape( pos.x, pos.y );
}

sf::RectangleShape& World::getShape( int x, int y )
{
  return mapShapes[x][y];
}

std::vector< Chunk& > surroundingChunks( vector2i pos )
{
  return surroundingChunks( pos.x, pos.y );
}

std::vector< Chunk& > surroundingChunks( int x, int y )
{
  std::vector< Chunk& > r;

  if ( x == 0 && y == 0 )
  {
    r.push_back( map[x+1][y  ] );
    r.push_back( map[x  ][y+1] );
    r.push_back( map[x+1][y+1] );
  }
  else if ( x > 0 && y == 0 && x < map.size() )
  {
    r.push_back( map[x-1][y  ] );
    r.push_back( map[x+1][y  ] );
    r.push_back( map[x-1][y-1] );
    r.push_back( map[x  ][y-1] );
    r.push_back( map[x+1][x-1] );
  }
  else if ( x == map.size() - 1 && y == 0 )
  {
    r.push_back( map[x-1][y  ] );
    r.push_back( map[x-1][y-1] );
    r.push_back( map[x  ][y-1] );
  }
  else if ( x == 0 && y > 0 && y < map[x].size() )
  {
    r.push_back( map[x  ][y-1] );
    r.push_back( map[x+1][y-1] );
    r.push_back( map[x+1][y  ] );
    r.push_back( map[x  ][y+1] );
    r.push_back( map[x+1][y+1] );
  }
  el

  else if ( x > 0 && y > 0 && x < map.size() && y < map[x].size() )
  {
    r.push_back( map[x-1][y-1] );
    r.push_back( map[x  ][y-1] );
    r.push_back( map[x+1][y-1] );
    r.push_back( map[x-1][y  ] );
    r.push_back( map[x+1][y  ] );
    r.push_back( map[x-1][y+1] );
    r.push_back( map[x  ][y+1] );
    r.push_back( map[x+1][y+1] );
  }
  else if ( x > 0 )
}

/*

  x|x|x
  -----
  x| |
  -----
   | |

*/