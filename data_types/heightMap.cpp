#include <map>
#include <string>
#include <SFML/System.hpp>
#include "heightMap.hpp"
#include "../defaults.hpp"


HeightCoord HeightMap::at( long long x, long long y, SIDE_LENGTH_TYPE side )
{
  HeightCoord r;
  r.side = side;

  if ( x >= 0 && y >= 0 )
  {
    r.x = side * (long long)( x / side );
    r.y = side * (long long)( y / side );

    return r;
  }
  else if ( x < 0 && y >= 0 )
  {
    r.x = side * (long long)( (x+1) / side );
    r.y = side * (long long)( y / side );
    r.x -= side;

    return r;
  }
  else if ( x >= 0 && y < 0 )
  {
    r.x = side * (long long)( x / side );
    r.y = side * (long long)( (y+1) / side );
    r.y -= side;

    return r;
  }
  else if ( x < 0 && y < 0 )
  {
    r.x = side * (long long)( (x+1) / side );
    r.y = side * (long long)( (y+1) / side );
    r.x -= side;
    r.y -= side;

    return r;
  }

  // just to block warning. this should NEVER happen.
  return r;
}

HEIGHT_TYPE& HeightMap::get( HeightCoord& p )
{
  if ( data.find(p) == data.end() )
    throw "HeightMap::get position " + std::to_string(p.x) + "," + std::to_string(p.y) + " not generated";

  return data[p];
}

void HeightMap::set( HeightCoord p, HEIGHT_TYPE value )
{
  data[p] = value;
}

void HeightMap::generate( long long x, long long y )
{
  SIDE_LENGTH_TYPE side = HEIGHT_CHUNK_SIZE;

  while ( side >= 1 )
  {
    HeightCoord p = at( x, y, side );

    try
    {
      get( p );
    }
    catch ( std::string error )
    {
      set( p, rand() % HEIGHT_RANGE - ( HEIGHT_RANGE / 2 ) );
    }

    side /= 2;
  }
}

HEIGHT_TYPE HeightMap::height( long long x, long long y )
{
  SIDE_LENGTH_TYPE side = HEIGHT_CHUNK_SIZE;
  HEIGHT_TYPE r;
  HeightCoord p;

  while ( side >= 1 )
  {
    p = at( x, y, side );

    try
    {
      r += get( p );
    }
    catch ( std::string error )
    {
      throw "HeightMap::height::" + error;
    }

    side /= 2;
  }

  return r;
}