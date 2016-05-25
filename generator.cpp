#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <SFML/System.hpp>
#include "world.hpp"
#include "window.hpp"

typedef sf::Vector2<unsigned int> vector2ui;
typedef sf::Vector2<double> vector2d;

void generateChunk( World& world, unsigned int x, unsigned int y )
{
  int type = 0;
  int r;
  vector2d land, water;
  std::vector< Chunk > chunks;

  land = LAND_PROB;
  water = WATER_PROB;

  if ( x > world.size().x - 1 || y > world.size().y - 1 )
    throw new std::string( "generateChunk:chunk is outside world " + std::to_string(x) + "," + std::to_string(y) + "." );

  chunks = surroundingChunks( world, x, y );

  for ( unsigned int c = 0; c < chunks.size(); c++ )
  {
    if ( chunks[c].type == LAND )
    {
      land.y += 5;
      water.x += 5;
    }
    else if ( chunks[c].type == WATER )
    {
      land.y -= 5;
      water.y -= 5;
    }
  }

  r = rand() % 100;

  if ( r >= land.x && r <= land.y )
    type = LAND;
  else if ( r >= water.x && r <= water.y )
    type = WATER;

  world.set( x, y, type );
}

void generateChunk( World& world, vector2ui pos )
{
  generateChunk( world, pos.x, pos.y );
}

std::thread generateChunkAsync( World& world, unsigned int x, unsigned int y )
{
  return async( launch::async, generateChunk, world, x, y );
}

std::thread generateChunkAsync( World& world, vector2ui pos )
{
  return generateChunkAsync( world, pos.x, pos.y );
}

void generate( World& world )
{
  unsigned int x = world.size().x / 2;
  unsigned int y = world.size().y / 2;
  generateChunk( world, x,y );

  std::cout << x << "," << y << std::endl;

  for ( unsigned int r = 0; r < VIEW_DISTANCE; r++ )
  {
    for ( unsigned int l = 0; l < r; l++ )
    {
      std::vector< std::thread > waitL;

      if ( l == 0 )
      {
        waitL.push_back( generateChunkAsync( world, x    , y - r ) );
        std::this_thread::sleep_for( std::chrono::milliseconds(500) );
        waitL.push_back( generateChunkAsync( world, x    , y + r ) );
        std::this_thread::sleep_for( std::chrono::milliseconds(500) );
        waitL.push_back( generateChunkAsync( world, x + r, y     ) );
        std::this_thread::sleep_for( std::chrono::milliseconds(500) );
        waitL.push_back( generateChunkAsync( world, x - 1, y     ) );
        std::this_thread::sleep_for( std::chrono::milliseconds(500) );
      }
      /*else
      {
        generateChunk( world, x + r, y - r );
        generateChunk( world, x - r, y - r );
        //generateChunk( world, x + r, y + r );
        //generateChunk( world, x - r, y + r );
      }*/

      for ( unsigned int t = 0; t < waitL.size(); t++ )
        waitL[t].wait();
    }
  }
}