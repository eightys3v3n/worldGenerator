#include <iostream>
#include <vector>
using namespace std;

#define STEP 1

void adj( vector< vector< int > >& data, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, int alt )
{
  for ( unsigned int x = x1; x < x2; x++ )
  {
    for ( unsigned int y = y1; y < y2; y++ )
    {
      data[x][y] += alt;
    }
  }
}

void divide( vector< vector< int > >& data, int side, int offsetX, int offsetY )
{
  for ( unsigned int x = 0; x < 2; x++ )
  {
    for ( unsigned int y = 0; y < 2; y++ )
    {
      adj( data, (x+offsetX) * side, (y+offsetY) * side, (x+1+offsetX) * side, (y+1+offsetY) * side, rand() % 2 );
    }
  }
}

int main()
{
  vector< vector< int > > data( 32, vector< int >(32) );

  srand(1337);

  int side = 16;

  for ( unsigned int s = 0; true; s++ )
  {
    cout << "side:" << side << endl;
    cout << " " << s*side << "," << s*side << endl;
    cout << " " << s*side << "," << s*side+1 << endl;
    cout << " " << s*side+1 << "," << s*side << endl;
    cout << " " << s*side+1 << "," << s*side+1 << endl;
    /*divide( data, side, s*side  , s*side   );
    divide( data, side, s*side  , s*side+1 );
    divide( data, side, s*side+1, s*side   );
    divide( data, side, s*side+1, s*side+1 );*/

    side /= 2;

    if ( side < 1 )
      break;
  }
/*  divide( data, 16, 0,0 );
    divide( data, 8, 0,0 );
      divide( data, 4, 0,0);
      divide( data, 4, 0,1);
      divide( data, 4, 1,0);
      divide( data, 4, 1,1);
    divide( data, 8, 0,1 );
      divide( data, 4, 0,4);
      divide( data, 4, 0,5);
      divide( data, 4, 1,4);
      divide( data, 4, 1,5);
    divide( data, 8, 1,0 );
    divide( data, 8, 1,1 );
  //divide( data, 2 );
  //divide( data, 1 );*/

  string buf = "";
  for ( unsigned int x = 0; x < data.size(); x++ )
  {
    for ( unsigned int y = 0; y < data[x].size(); y++ )
    {
      buf += to_string( data[y][x] ) + " ";

      if ( y == 15 )
        buf += " ";
    }

    buf += '\n';

    if ( x == 15 )
      buf += '\n';
  }

  cout << buf << endl;

  return 0;
}