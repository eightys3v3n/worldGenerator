#include "world.hpp"

void generate( World& world )
{
  for ( int x = 0; x < world.size().x; x++ )
  {
    for ( int y = 0; y < world.size().y; y++ )
    {
      if ( x % 10 == 0 && y % 10 == 0 )
      {
        if ( rand() % 2 == 0 )
          world.set( x, y, GREEN );
        else
          world.set( x, y, BLUE );
      }
    }
  }
}