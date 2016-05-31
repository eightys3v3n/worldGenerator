#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <chrono>
#include <queue>
#include <SFML/System.hpp>
#include "world.hpp"
#include "window.hpp"
#include "defaults.hpp"
#include "data_types/queue.cpp"

typedef sf::Vector2<unsigned int> vector2ui;
typedef sf::Vector2<double> vector2d;

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

/*void generateChunkAsync( World* world, ChunkQueue* chunk )
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
}*/

void generate( World* world )
{
  std::deque< Queue< vector2ui > > s;
  //std::vector< Queue< int > > s;
  std::vector< std::thread > threads;
  unsigned int x = world->size().x / 2;
  unsigned int y = world->size().y / 2;
  // generateChunk( world, {x,y} );

  std::this_thread::sleep_for( std::chrono::milliseconds(1000) ); // wait for drawing to initialize

  for ( unsigned int r = 0; r < VIEW_DISTANCE; r++ )
  {
    for ( unsigned int l = 0; l <= r; l++ ) // expand in the x direction
    {
      s.resize( s.size() + 1 );

      if ( l == 0 )
      {
        s[ s.size() - 1 ].push( vector2ui{x-r, y} );
        s[ s.size() - 1 ].push( vector2ui{x+r, y} );
      }
      else
      {
        s[ s.size() - 1 ].push( vector2ui{x+r, y-l} );
        s[ s.size() - 1 ].push( vector2ui{x-r, y-l} );
        s[ s.size() - 1 ].push( vector2ui{x+r, y+l} );
        s[ s.size() - 1 ].push( vector2ui{x-r, y+l} );
      }
    }

    for ( unsigned int l = 0; l < r; l++ ) // expand in the y direction
    {
      s.resize( s.size() + 1 );

      if ( l == 0 )
      {
        s[ s.size() - 1 ].push( vector2ui{x, y-r} );
        s[ s.size() - 1 ].push( vector2ui{x, y+r} );
      }
      else
      {
        s[ s.size() - 1 ].push( vector2ui{x-l, y+r} );
        s[ s.size() - 1 ].push( vector2ui{x-l, y-r} );
        s[ s.size() - 1 ].push( vector2ui{x+l, y+r} );
        s[ s.size() - 1 ].push( vector2ui{x+l, y-r} );
      }
    }
  }

  for ( unsigned int i = 0; i < s.size(); i++ )
  {
    while ( ! s[i].empty() )
    {
      world->set( s[i].front().x, s[i].front().y, -1 );
      std::cout << " " << s[i].front().x << "," << s[i].front().y << std::endl;
      s[i].pop();
    }

    std::cout << "generated parallel " << i << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds(50) );
  }

  /*std::vector< std::vector< std::packaged_task< void( World*, ChunkQueue* ) > > > chunks;

  chunks.resize( world->size().x );
  for ( unsigned int x = 0; x < world->size().x; x++ )
  {
    chunks[x].resize( world->size().y );
    for ( unsigned int y = 0; y < world->size().y; y++ )
    {
      chunks[x][y] = std::packaged_task< void( World*, ChunkQueue* ) >( generateChunkAsync )

    }
  }*/
}