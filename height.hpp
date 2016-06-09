#ifndef HEIGHT_
#define HEIGHT_

#include <SFML/System.hpp>

typedef sf::Vector2<unsigned int> vector2ui;

void generateHeight( std::vector< std::vector< int > >& data, vector2ui start, vector2ui end );
std::vector< std::vector< int > > generateHeights( vector2ui size );

#endif // HEIGHT_