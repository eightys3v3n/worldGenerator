#include <iostream>
#include <map>
#include <cmath>
using namespace std;

#define SIZE 8
#define HEIGHT_RANGE 3

struct HeightCoord
{
  int x = 0;
  int y = 0;
  int side = 0;
};

class HeightMap
{
public:
  // returns the sum of the heights of side=1 to side=SIZE.
  int height( int x, int y );

  // generates all required levels to generate x,y,side.
  void generate( int x, int y );

  // returns the height of x,y,side.
  int& get( HeightCoord p );
  int& get( int x, int y, int side );

private:
  map< int, pair< int, map< int, pair< int, map< int, int >>>>> data;

  // returns the Coords of x,y,side in data. always use this to get the position of any element!
  HeightCoord at( int x, int y, int side );


  // sets the height value for the side length of x and y.
  void set( HeightCoord p, int value );
  void set( int x, int y, int side, int value );
};

HeightCoord HeightMap::at( int x, int y, int side )
{
  if ( x >= 0 && y >= 0 )
  {
    x = side * (int)( x / side );
    y = side * (int)( y / side );

    return {x,y,side};
  }
  else if ( x < 0 && y >= 0 )
  {
    x = side * (int)( (x+1) / side );
    y = side * (int)( y / side );
    x -= side;

    return {x,y,side};
  }
  else if ( x >= 0 && y < 0 )
  {
    x = side * (int)( x / side );
    y = side * (int)( (y+1) / side );
    y -= side;

    return {x,y,side};
  }
  else if ( x < 0 && y < 0 )
  {
    x = side * (int)( (x+1) / side );
    y = side * (int)( (y+1) / side );
    x -= side;
    y -= side;

    return {x,y,side};
  }

  // just to block warning. this should NEVER happen.
  return {0,0,0};
}

int& HeightMap::get( HeightCoord p )
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

int& HeightMap::get( int x, int y, int side )
{
  return get( at( x, y, side ) );
}

void HeightMap::set( HeightCoord p, int value )
{
  data[p.x].second[p.y].second[p.side] = value;
}

void HeightMap::set( int x, int y, int side, int value )
{
  set( at( x, y, side ), value );
}

void HeightMap::generate( int x, int y )
{
  int side = SIZE;

  while ( side >= 1 )
  {
    HeightCoord p = at( x, y, side );

    try
    {
      get( p );
    }
    catch ( string error )
    {
      set( p, rand() % HEIGHT_RANGE - ( HEIGHT_RANGE / 2 ) );
      cout << "+ generating " << p.x << "," << p.y << "," << p.side << endl;
    }

    side /= 2;
  }
}

int HeightMap::height( int x, int y )
{
  int side = SIZE;
  int r;

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

int main()
{
  HeightMap data;

  int x, y;
  string buf;

  srand(175692);

  while ( x != 1337 && y != 1337 )
  {
    cin >> buf;

    try
    {
      x = stoi( buf.substr( 0, buf.find(',') ) );
      y = stoi( buf.substr( buf.find(',') + 1 ) );
    }
    catch (...)
    {
      cout << "both coordinates need to be integers" << endl;
      continue;
    }

    try
    {
      data.height( x, y );

      cout << "height of the " << x << "," << y << " stack." << endl;

      for ( int s = 1; s <= SIZE; s *= 2 )
      {
        cout << "  " << data.get( x, y, s ) << endl;
      }

      cout << " total height " << data.height( x,y ) << endl;
    }
    catch ( string error )
    {
      cout << error << endl;

      data.generate( x, y );
    }
  }

  return false;
}