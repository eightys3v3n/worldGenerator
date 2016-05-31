#ifndef CHUNK_
#define CHUNK_

#include <mutex>
#include <condition_variable>
#include <queue>
#include <SFML/System.hpp>

#ifndef CHUNK_SIZE
#define CHUNK_SIZE 10 // chunk width 7 height in pixels; chunks are square
#endif // CHUNK_SIZE

// probabilities of being a given type of land; between 0-99; must not overlap
#ifndef LAND
#define LAND 1
#define LAND_PROB sf::Vector2<double>{ .x = 0, .y = 69 }
#endif // LAND

#ifndef WATER
#define WATER 2
#define WATER_PROB sf::Vector2<double>{ .x = 70, .y = 99 }
#endif // WATER

struct Chunk
{
  int type = 0;
};

class Queue
{
public:
  void push(int new);
  int pop();
  bool empty();

private:
  queue<int> q;
  condition_variable cv;
  mutex m;
};

#endif // CHUNK_