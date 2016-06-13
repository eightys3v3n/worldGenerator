#ifndef WORLD_
#define WORLD_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "defaults.hpp"
#include "data_types/chunk.cpp"
#include "data_types/heightMap.hpp"

typedef sf::Vector2<unsigned int> vector2ui;
typedef sf::Vector2<long long> vector2ll;

class World
{
public:
  void init( long long x, long long y );
  bool exists( long long x, long long y );
  long long size();
  void set( long long x, long long y, int t );
  void set( vector2ll pos, int t );
  Chunk* get( long long x, long long y );
  Chunk* get( vector2ll pos );
  HEIGHT_TYPE getHeight( vector2ll pos );
  HEIGHT_TYPE getHeight( long long x, long long y );

  sf::CircleShape& shape( long long x, long long y );
  sf::CircleShape& shape( vector2ll pos );

private:
  std::map< long long, std::map< long long, Chunk > > chunkData;
  heightMap heightData;
};

std::vector< Chunk* > surroundingChunks( World* world, long long x, long long y );
std::vector< Chunk* > surroundingChunks( World* world, vector2ll pos );

#endif // WORLD_