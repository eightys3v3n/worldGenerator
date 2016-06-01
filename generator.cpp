#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <queue>
#include <condition_variable>
#include <SFML/System.hpp>
#include "defaults.hpp"
#include "world.hpp"
#include "data_types/queue.hpp"
#include "data_types/entity.hpp"

typedef sf::Vector2<unsigned int> vector2ui;
typedef sf::Vector2<long long> vector2ll;
typedef sf::Vector2<double> vector2d;

void generateChunk( bool* running, World* world, Queue<vector2ll>* queue, Queue<vector2ll>* finQ )
{
  int type = 0;
  int r;
  vector2d land, water;
  vector2ll pos;
  std::vector< Chunk* > chunks;

  land = LAND_PROB;
  water = WATER_PROB;

  while ( *running )
  {
    pos = queue->first();

    if ( ! *running )
      break;

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

    std::this_thread::sleep_for( std::chrono::milliseconds( GENERATION_DELAY ) );

    world->set( pos.x, pos.y, type );
    finQ->push(pos);
  }
}

std::deque< Queue< vector2ll > > generateSeq( World* world, Entity* player )
{
  std::deque< Queue< vector2ll > > s;
  long long x = player->x;
  long long y = player->y;

  for ( unsigned int r = 0; r <= VIEW_DISTANCE; r++ )
  {
    if ( r == 0 )
    {
      if ( world->get(x,y)->type == 0 )
      {
        s.resize( s.size() + 1 );
        s[ s.size() - 1].push( vector2ll{x,y} );
      }
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

  return s;
}

void generate( bool* running, World* world, Entity* player, Queue<vector2ll>* chunks, std::condition_variable* in, Queue<vector2ll>* finChunks )
{
  //std::mutex m; // for use with 'notify when to generate'
  std::mutex ch;
  std::vector<std::thread> threads;
  unsigned int queued = 0;

  while ( *running )
  {
    std::unique_lock<std::mutex> lk1(ch);
    //std::unique_lock<std::mutex> lk(m); // for use with 'notify when to generate'
    //cv.wait(lk); // for use with 'notify when to generate'

    // order to generate chunks.
    std::deque< Queue< vector2ll > > s;

    // TODO:currently generates entire sequence but only needs next level.
    s = generateSeq( world, player );

    std::cerr << "waiting for " << queued << " chunks." << std::endl;
    finChunks->untilSize( queued );
    finChunks->clear();

    queued = s[0].size();

    while ( ! s[0].empty() )
      chunks->push( s[0].first() );
  }

  // to resume chunk generation threads; they will not generate a chunk if running is false.
  for ( unsigned int t = 0; t < THREADS; t++ )
    chunks->push( vector2ll{0,0} );
}