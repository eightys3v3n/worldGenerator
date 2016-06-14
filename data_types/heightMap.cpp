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

HEIGHT_TYPE& HeightMap::get( long long x, long long y, SIDE_LENGTH_TYPE side )
{
  HeightCoord r = at( x, y, side );
  return get( r );
}

void HeightMap::set( long long x, long long y, SIDE_LENGTH_TYPE side, HEIGHT_TYPE value )
{
  HeightCoord r = at( x, y, side );
  set( r, value );
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

bool HeightMap::generated( long long x, long long y )
{
  HeightCoord r{ x, y, 1 };

  if ( data.find(r) == data.end() )
    return false;

  return true;
}