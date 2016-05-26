#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <chrono>
#include <future>
#include <SFML/System.hpp>
#include "world.hpp"
#include "window.hpp"

typedef sf::Vector2<unsigned int> vector2ui;
typedef sf::Vector2<double> vector2d;

struct ChunkQueue
{
  vector2ui pos;
  std::promise< int > p;
  std::future< int > f = p.get_future();
  std::vector< std::future< int >* > r;
};

void generateChunk( World* world, vector2ui pos )
{
  int type = 0;
  int r;
  vector2d land, water;
  std::vector< Chunk > chunks;

  land = LAND_PROB;
  water = WATER_PROB;

  if ( pos.x > world->size().x - 1 || pos.y > world->size().y - 1 )
    throw new std::string( "generateChunk:chunk is outside world " + std::to_string(pos.x) + "," + std::to_string(pos.y) + "." );

  chunks = surroundingChunks( world, pos.x, pos.y );

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

  world->set( pos.x, pos.y, type );
}

void generateChunkAsync( World* world, ChunkQueue* chunk )
{
  for ( unsigned int r = 0; r < chunk->r.size(); r++ )
  {
    //std::cout << l << ":" << c << "|waiting for " << r << std::endl;
    chunk->r[r]->wait();
  }

  //std::cout << "generating chunk " << 25 - chunk->pos.x << "," << 25 - chunk->pos.y << std::endl;
  generateChunk( world, chunk->pos );
  std::this_thread::sleep_for( std::chrono::milliseconds(1000) );

  //std::cout << l << ":" << c << "|finished" << std::endl;
  chunk->p.set_value(true);
}

void generate( World* world )
{
  std::vector< std::vector< ChunkQueue > > s;
  std::vector< std::thread > threads;
  unsigned int x = world->size().x / 2;
  unsigned int y = world->size().y / 2;
  generateChunk( world, {x,y} );

  std::this_thread::sleep_for( std::chrono::milliseconds(2000) ); // wait for drawing to initialize

  /*for ( unsigned int r = 0; r < VIEW_DISTANCE; r++ )
  {
    for ( unsigned int l = 0; l < r; l++ )
    {
      s.resize( s.size() + 1 );

      if ( l == 0 )
      {
        s[ s.size() - 1].resize( s[ s.size() - 1].size() + 1 );
        s[ s.size() - 1 ][ s[ s.size() - 1].size() - 1 ].pos = vector2ui(x  ,y-1);

        s[ s.size() - 1].resize( s[ s.size() - 1].size() + 1 );
        s[ s.size() - 1 ][ s[ s.size() - 1].size() - 1 ].pos = vector2ui(x  ,y+1);
      }
      else
      {
        s[ s.size() - 1].resize( s[ s.size() - 1].size() + 1 );
        s[ s.size() - 1 ][ s[ s.size() - 1].size() - 1 ].pos = vector2ui(x+r,y-1);

        s[ s.size() - 1].resize( s[ s.size() - 1].size() + 1 );
        s[ s.size() - 1 ][ s[ s.size() - 1].size() - 1 ].pos = vector2ui(x-r,y-1);

        s[ s.size() - 1].resize( s[ s.size() - 1].size() + 1 );
        s[ s.size() - 1 ][ s[ s.size() - 1].size() - 1 ].pos = vector2ui(x+r,y+1);

        s[ s.size() - 1].resize( s[ s.size() - 1].size() + 1 );
        s[ s.size() - 1 ][ s[ s.size() - 1].size() - 1 ].pos = vector2ui(x-r,y+1);
      }
    }
  }*/

  struct temp
  {
    vector2ui pos;
    std::packaged_task< void( World*,)
  }

  std::vector< std::vector< std::packaged_task< void( World*, ChunkQueue* ) > > > chunks;

  chunks.resize( world->size().x );
  for ( unsigned int x = 0; x < world->size().x; x++ )
  {
    chunks[x].resize( world->size().y );
    for ( unsigned int y = 0; y < world->size().y; y++ )
    {
      chunks[x][y] = std::packaged_task< void( World*, ChunkQueue* ) >( generateChunkAsync )

    }
  }



}