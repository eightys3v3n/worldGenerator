#ifndef CHUNK_
#define CHUNK_

#include <SFML/System.hpp>

#define CHUNK_SIZE 10 // chunk width 7 height in pixels; chunks are square

// probabilities of being a given type of land; between 0-99; must not overlap
#define LAND 1
#define LAND_PROB sf::Vector2<double>{ .x = 0, .y = 69 }
#define WATER 2
#define WATER_PROB sf::Vector2<double>{ .x = 70, .y = 99 }

struct Chunk
{
  int type = 0;
};

#endif // CHUNK_