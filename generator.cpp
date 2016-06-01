#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <SFML/System.hpp>
#include "defaults.hpp"
#include "world.hpp"
#include "window.hpp"
#include "data_types/queue.hpp"
#include "data_types/entity.hpp"

typedef sf::Vector2<unsigned int> vector2ui;
typedef sf::Vector2<double> vector2d;

extern bool running;

void generateChunk( World* world, Queue* queue )
{
  while ( running )
  {
    int type = 0;
    int r;
    vector2d land, water;
    std::vector< Chunk* > chunks;
    vector2ll pos = queue.first();

    land = LAND_PROB;
    water = WATER_PROB;

    chunks = surroundingChunks( world, pos.x, pos.y );

    for ( unsigned int c = 0; c < chunks.size(); c++ )
    {
      if ( chunks[c]->type == LAND )
      {
        land.y += 5;
        water.x += 5;
      }
      else if ( chunks[c]->type == WATER )
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
}

void generate( World* world, Entity* player, Queue<vector2ll>* q, std::condition_variable* cv )
{
  std::mutex m;

  while ( running )
  {
    std::unique_lock<std::mutex> lk(m);
    while ( q->empty() )
      cv->wait(lk);

    std::deque< Queue< vector2ll > > s;
    std::vector< std::thread > threads;

    long long x = q->front().x;
    long long y = q->front().y;
    q->pop();

    // chunk generation sequence algorythm
    for ( unsigned int r = 0; r <= VIEW_DISTANCE; r++ )
    {
      if ( r == 0 )
      {
        s.resize( s.size() + 1 );
        s[ s.size() - 1].push( vector2ll{0,0} );
        continue;
      }

      for ( unsigned int l = 0; l <= r; l++ ) // expand in the x direction
      {
        s.resize( s.size() + 1 );

        if ( l == 0 )
        {
          if ( world->get(x-r, y)->type == 0 )
            s[ s.size() - 1 ].push( vector2ll{x-r, y} );

          if ( world->get(x+r, y)->type == 0 )
            s[ s.size() - 1 ].push( vector2ll{x+r, y} );
        }
        else
        {
          if ( world->get(x+r, y-l)->type == 0 )
            s[ s.size() - 1 ].push( vector2ll{x+r, y-l} );

          if ( world->get(x-r, y-l)->type == 0 )
            s[ s.size() - 1 ].push( vector2ll{x-r, y-l} );

          if ( world->get(x+r, y+l)->type == 0 )
            s[ s.size() - 1 ].push( vector2ll{x+r, y+l} );

          if ( world->get(x-r, y+l)->type == 0 )
            s[ s.size() - 1 ].push( vector2ll{x-r, y+l} );
        }

        if ( s[ s.size() - 1 ].size() == 0 )
          s.resize( s.size() - 1 );
      }

      for ( unsigned int l = 0; l < r; l++ ) // expand in the y direction
      {
        s.resize( s.size() + 1 );

        if ( l == 0 )
        {
          if ( world->get(x, y-r)->type == 0 )
            s[ s.size() - 1 ].push( vector2ll{x, y-r} );

          if ( world->get(x, y+r)->type == 0 )
            s[ s.size() - 1 ].push( vector2ll{x, y+r} );
        }
        else
        {
          if ( world->get(x-l, y+r)->type == 0 )
            s[ s.size() - 1 ].push( vector2ll{x-l, y+r} );

          if ( world->get(x-l, y-r)->type == 0 )
            s[ s.size() - 1 ].push( vector2ll{x-l, y-r} );

          if ( world->get(x+l, y+r)->type == 0 )
            s[ s.size() - 1 ].push( vector2ll{x+l, y+r} );

          if ( world->get(x+l, y-r)->type == 0 )
            s[ s.size() - 1 ].push( vector2ll{x+l, y-r} );
        }

        if ( s[ s.size() - 1 ].size() == 0 )
          s.resize( s.size() - 1 );
      }
    }
    // end chunk generation sequence algorythm

    for ( unsigned int i = 0; i < s.size(); i++ )
    {
      while ( ! s[i].empty() )
      {
        threads.push_back( thread( generateChunk, world, s[i].front()) );
      }

      std::cout << "generated parallel " << i << std::endl;
      std::this_thread::sleep_for( std::chrono::milliseconds(100) );
    }
  }
}