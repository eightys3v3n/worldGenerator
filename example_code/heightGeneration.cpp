#include <iostream>
#include <vector>
#include "height.hpp"
using namespace std;

#define STEP 1

/*vector< vector< int > > data( 32, vector< int >(32) );

void generate( unsigned int startx, unsigned int starty, unsigned int endx, unsigned int endy )
{
  if ( endx - startx < 2 || endy - starty < 2 )
    return;

  int one = rand() % ( STEP * 3 ) - STEP;
  int two = rand() % ( STEP * 3 ) - STEP;
  int three = rand() % ( STEP * 3 ) - STEP;
  int four = rand() % ( STEP * 3 ) - STEP;

  unsigned int middlex = (endx - startx) / 2 + startx;
  unsigned int middley = (endy - starty) / 2 + starty;

  for ( unsigned int x = startx; x < middlex; x++ )
    for ( unsigned int y = starty; y < middley; y++ )
      data[x][y] += one;
  generate( startx, starty, middlex, middley );

  for ( unsigned int x = middlex; x < endx; x++ )
    for ( unsigned int y = starty; y < middley; y++ )
      data[x][y] += two;
  generate( middlex, starty, endx, middley );

  for ( unsigned int x = startx; x < middlex; x++ )
    for ( unsigned int y = middley; y < endy; y++ )
      data[x][y] += three;
  generate( startx, middley, middlex, endy );

  for ( unsigned int x = middlex; x < endx; x++ )
    for ( unsigned int y = middley; y < endy; y++ )
      data[x][y] += four;
  generate( middlex, middley, endx, endy );
}*/

void printGrid( vector< vector< int > >& data )
{
  string buf = "";
  string grid = "";

  for ( unsigned int x = 0; x < data.size(); x++ )
  {
    for ( unsigned int y = 0; y < data[x].size(); y++ )
    {
      buf = to_string( data[y][x] );

      while ( buf.length() < 2 )
        buf = " " + buf;

      grid += buf + " ";

      if ( y == 15 )
        grid += " | ";
    }

    grid += '\n';

    if ( x == 15 )
      grid += '\n';
  }

  cout << grid << endl;
}

int main()
{
  srand(1337);

  vector< vector< int > > data;

  data = generateHeights({32,32});

  printGrid( data );

  return 0;
}