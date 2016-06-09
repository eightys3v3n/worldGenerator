#include <vector>
#include <SFML/System.hpp>

#define STEP 1

typedef sf::Vector2<unsigned int> vector2ui;

void generateHeight( std::vector< std::vector< int > >& data, vector2ui start, vector2ui end )
{
  if ( end.x - start.x < 2 || end.y - start.y < 2 )
    return;

  int one = rand() % ( STEP * 3 ) - STEP;
  int two = rand() % ( STEP * 3 ) - STEP;
  int three = rand() % ( STEP * 3 ) - STEP;
  int four = rand() % ( STEP * 3 ) - STEP;

  vector2ui middle;
  middle.x = (end.x - start.x) / 2 + start.x;
  middle.y = (end.y - start.y) / 2 + start.y;

  for ( unsigned int x = start.x; x < middle.x; x++ )
    for ( unsigned int y = start.y; y < middle.y; y++ )
      data[x][y] += one;
  generateHeight( data, start, middle );

  for ( unsigned int x = middle.x; x < end.x; x++ )
    for ( unsigned int y = start.y; y < middle.y; y++ )
      data[x][y] += two;
  generateHeight( data, vector2ui{middle.x, start.y}, vector2ui{end.x, middle.y} );

  for ( unsigned int x = start.x; x < middle.x; x++ )
    for ( unsigned int y = middle.y; y < end.y; y++ )
      data[x][y] += three;
  generateHeight( data, vector2ui{start.x, middle.y}, vector2ui{middle.x, end.y} );

  for ( unsigned int x = middle.x; x < end.x; x++ )
    for ( unsigned int y = middle.y; y < end.y; y++ )
      data[x][y] += four;
  generateHeight( data, middle, end );
}

std::vector< std::vector< int > > generateHeights( vector2ui size )
{
  std::vector< std::vector< int > > data( size.x, std::vector< int >(size.y) );

  generateHeight( data, vector2ui{0,0}, vector2ui{size.x,size.y} );

  return data;
}
