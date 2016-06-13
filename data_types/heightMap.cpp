#include <map>
#include <string>
#include <SFML/System.hpp>
#include "../defaults.hpp"

typedef sf::Vector2<long long> vector2ll;

#define SIDE_LENGTH_TYPE int
#define HEIGHT_TYPE int

struct HeightCoord
{
  vector2ll p;
  SIDE_LENGTH_TYPE side;
}

class HeightMap
{
public:
  // returns the sum of the heights of side=1 to side=HEIGHT_CHUNK_SIZE.
  HEIGHT_TYPE height( vector2ll p );

  // generates all required levels to generate x,y,side.
  void generate( vector2ll p );

private:
  std::map< vector2ll, std::pair< HEIGHT_TYPE, std::map< COORDS_TYPE, HEIGHT_TYPE >>> data;

  // returns the Coords of x,y,side in data. always use this to get the position of any element!
  HeightCoord at( vector2ll p, SIDE_LENGTH_TYPE side );

  // returns the height of x,y,side.
  HEIGHT_TYPE& get( vector2ll p, SIDE_LENGTH_TYPE side );

  // sets the height value for the side length of x and y.
  void set( vector2ll p, SIDE_LENGTH_TYPE side, HEIGHT_TYPE value );
};

HeightCoord HeightMap::at( vector2ll p, SIDE_LENGTH_TYPE side )
{
  if ( p.x >= 0 && p.y >= 0 )
  {
    p.x = side * (COORDS_TYPE)( p.x / side );
    p.y = side * (COORDS_TYPE)( p.y / side );

    return {p.x,p.y,side};
  }
  else if ( p.x < 0 && p.y >= 0 )
  {
    p.x = side * (COORDS_TYPE)( (p.x+1) / side );
    p.y = side * (COORDS_TYPE)( p.y / side );
    p.x -= side;

    return {p.x,p.y,side};
  }
  else if ( p.x >= 0 && p.y < 0 )
  {
    p.x = side * (COORDS_TYPE)( p.x / side );
    p.y = side * (COORDS_TYPE)( (p.y+1) / side );
    p.y -= side;

    return {p.x,p.y,side};
  }
  else if ( p.x < 0 && p.y < 0 )
  {
    p.x = side * (COORDS_TYPE)( (p.x+1) / side );
    p.y = side * (COORDS_TYPE)( (p.y+1) / side );
    p.x -= side;
    p.y -= side;

    return {p.x,p.y,side};
  }

  // just to block warning. this should NEVER happen.
  return {0,0,0};
}

HEIGHT_TYPE& HeightMap::get( vector2ll p, SIDE_LENGTH_TYPE side )
{
  if ( data.find(p.x) != data.end() )
  {
    if ( data[p.x].second.find(p.y) != data[p.x].second.end() )
    {
      if ( data[p.x].second[p.y].second.find(side) != data[p.x].second[p.y].second.end() )
        return data[p.x].second[p.y].second[side];
      else
        throw "HeightMap::get position " + std::to_string(p.x) + "," + std::to_string(p.y) + " not generated";
    }
    else
      throw "HeightMap::get position " + std::to_string(p.x) + "," + std::to_string(p.y) + " not generated";
  }
  else
    throw "HeightMap::get position " + std::to_string(p.x) + "," + std::to_string(p.y) + " not generated";
}

void HeightMap::set( vector2ll p, SIDE_LENGTH_TYPE side, HEIGHT_TYPE value )
{
  data[p.x].second[p.y].second[side] = value;
}

void HeightMap::generate( vector2ll p )
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

HEIGHT_TYPE HeightMap::height( vector2ll p )
{
  SIDE_LENGTH_TYPE side = HEIGHT_CHUNK_SIZE;
  HEIGHT_TYPE r;

  while ( side >= 1 )
  {
    try
    {
      r += get( x, y, side );
    }
    catch ( std::string error )
    {
      throw "HeightMap::height::" + error;
    }

    side /= 2;
  }
}