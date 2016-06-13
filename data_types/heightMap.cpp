#include <map>
#include <string>

#define COORDS_TYPE int
#define SIDE_LENGTH_TYPE int
#define HEIGHT_TYPE int

struct HeightCoord
{
  COORDS_TYPE x = 0;
  COORDS_TYPE y = 0;
  SIDE_LENGTH_TYPE side = 0;
};

class HeightMap
{
public:
  // returns the sum of the heights of side=1 to side=SIZE.
  HEIGHT_TYPE height( COORDS_TYPE x, COORDS_TYPE y );

  // generates all required levels to generate x,y,side.
  void generate( COORDS_TYPE x, COORDS_TYPE y );

private:
  map< COORDS_TYPE, pair< HEIGHT_TYPE, map< COORDS_TYPE, pair< HEIGHT_TYPE, map< COORDS_TYPE, HEIGHT_TYPE >>>>> data;

  // returns the Coords of x,y,side in data. always use this to get the position of any element!
  HeightCoord at( COORDS_TYPE x, COORDS_TYPE y, SIDE_LENGTH_TYPE side );

  // returns the height of x,y,side.
  HEIGHT_TYPE& get( HeightCoord p );
  HEIGHT_TYPE& get( COORDS_TYPE x, COORDS_TYPE y, SIDE_LENGTH_TYPE side );

  // sets the height value for the side length of x and y.
  void set( HeightCoord p, HEIGHT_TYPE value );
  void set( COORDS_TYPE x, COORDS_TYPE y, SIDE_LENGTH_TYPE side, HEIGHT_TYPE value );
};

HeightCoord HeightMap::at( COORDS_TYPE x, COORDS_TYPE y, SIDE_LENGTH_TYPE side )
{
  if ( x >= 0 && y >= 0 )
  {
    x = side * (COORDS_TYPE)( x / side );
    y = side * (COORDS_TYPE)( y / side );

    return {x,y,side};
  }
  else if ( x < 0 && y >= 0 )
  {
    x = side * (COORDS_TYPE)( (x+1) / side );
    y = side * (COORDS_TYPE)( y / side );
    x -= side;

    return {x,y,side};
  }
  else if ( x >= 0 && y < 0 )
  {
    x = side * (COORDS_TYPE)( x / side );
    y = side * (COORDS_TYPE)( (y+1) / side );
    y -= side;

    return {x,y,side};
  }
  else if ( x < 0 && y < 0 )
  {
    x = side * (COORDS_TYPE)( (x+1) / side );
    y = side * (COORDS_TYPE)( (y+1) / side );
    x -= side;
    y -= side;

    return {x,y,side};
  }

  // just to block warning. this should NEVER happen.
  return {0,0,0};
}

HEIGHT_TYPE& HeightMap::get( HeightCoord p )
{
  if ( data.find(p.x) != data.end() )
  {
    if ( data[p.x].second.find(p.y) != data[p.x].second.end() )
    {
      if ( data[p.x].second[p.y].second.find(p.side) != data[p.x].second[p.y].second.end() )
        return data[p.x].second[p.y].second[p.side];
      else
        throw "HeightMap::get position " + to_string(p.x) + "," + to_string(p.y) + " not generated";
    }
    else
      throw "HeightMap::get position " + to_string(p.x) + "," + to_string(p.y) + " not generated";
  }
  else
    throw "HeightMap::get position " + to_string(p.x) + "," + to_string(p.y) + " not generated";
}

HEIGHT_TYPE& HeightMap::get( COORDS_TYPE x, COORDS_TYPE y, SIDE_LENGTH_TYPE side )
{
  return get( at( x, y, side ) );
}

void HeightMap::set( HeightCoord p, HEIGHT_TYPE value )
{
  data[p.x].second[p.y].second[p.side] = value;
}

void HeightMap::set( COORDS_TYPE x, COORDS_TYPE y, SIDE_LENGTH_TYPE side, HEIGHT_TYPE value )
{
  set( at( x, y, side ), value );
}

void HeightMap::generate( COORDS_TYPE x, COORDS_TYPE y )
{
  SIDE_LENGTH_TYPE side = SIZE;

  while ( side >= 1 )
  {
    HeightCoord p = at( x, y, side );

    try
    {
      get( p );
    }
    catch ( string error )
    {
      set( p, rand() % HEIGHT_TYPE_RANGE - ( HEIGHT_TYPE_RANGE / 2 ) );
    }

    side /= 2;
  }
}

HEIGHT_TYPE HeightMap::height( COORDS_TYPE x, COORDS_TYPE y )
{
  SIDE_LENGTH_TYPE side = SIZE;
  HEIGHT_TYPE r;

  while ( side >= 1 )
  {
    try
    {
      r += get( x, y, side );
    }
    catch ( string error )
    {
      throw "HeightMap::height::" + error;
    }

    side /= 2;
  }
}