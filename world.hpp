#ifndef WORLD_
#define WORLD_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "chunk.hpp"

#define GREEN 1
#define BLUE 2
#define CHUNK_SIZE 10

typedef sf::Vector2i vector2i;

class World
{
private:
  std::vector< std::vector< Chunk > > map;
  std::vector< std::vector< sf::RectangleShape > > mapShapes;

public:
  vector2i size();
  void size( vector2i newSize );
  void size( int x, int y );
  void set( vector2i pos, int newType );
  void set( int x, int y, int newType );
  int getType( vector2i pos );
  int getType( int x, int y );
  sf::RectangleShape& getShape( vector2i pos );
  sf::RectangleShape& getShape( int x, int y );
  std::vector< Chunk& > surroundingChunks( vector2i pos );
  std::vector< Chunk& > surroundingChunks( int x, int y );
};

#endif // WORLD_