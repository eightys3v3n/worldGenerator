#ifndef WORLD_
#define WORLD_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "chunk.hpp"

#define VIEW_DISTANCE 4

typedef sf::Vector2<unsigned int> vector2ui;

struct World
{
  std::vector< std::vector< Chunk > > map;
  std::vector< std::vector< sf::RectangleShape > > mapShapes;

  vector2ui size();
  void size( unsigned int x, unsigned int y );
  void size( vector2ui newSize );
  void set( unsigned int x, unsigned int y, int newType );
  void set( vector2ui pos, int newType );
  int getType( unsigned int x, unsigned int y );
  int getType( vector2ui pos );
  sf::RectangleShape& getShape( unsigned int x, unsigned int y );
  sf::RectangleShape& getShape( vector2ui pos );
};

std::vector< Chunk > surroundingChunks( World& world, unsigned int x, unsigned int y );
std::vector< Chunk > surroundingChunks( World& world, vector2ui pos );

#endif // WORLD_