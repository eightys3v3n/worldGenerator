#include <iostream>
#include "world_test.hpp"
using namespace std;

int main()
{
  World world;
  world.size(3,3);
  for ( unsigned int x = 0; x < world.size().x; x++ )
    for ( unsigned int y = 0; y < world.size().y; y++ )
      world.set( x,y, 1 );

  try
  {
    test::surroundingChunks( world );
  }
  catch ( string* error )
  {
    cout << *error << endl;
  }

  return false;
}