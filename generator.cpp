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

void generateChunk( bool* running, World* world, Queue<vector2ll>* queue )
{
  while ( *running )
  {
    int type = 0;
    int r;
    vector2d land, water;
    std::vector< Chunk* > chunks;
    vector2ll pos = queue->first();

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

void generate( bool* running, World* world, Entity* player, Queue<vector2ll>* chunks, std::condition_variable* cv )
{
  std::mutex m;
  std::vector<std::thread> threads;

  while ( running )
  {
    std::unique_lock<std::mutex> lk(m);

    // for use once i impliment a 'generate new chunks' event.
    //cv.wait(lk);

    // order to generate chunks.
    std::deque< Queue< vector2ll > > s;

    // TODO:currently generates entire sequence but only needs next level.
    s = generateSeq( world, player );
    std::deque< Queue< vector2ll > > a = generateSeq(world,player);

    while ( ! a[0].empty() )
    {
      if ( world->get(a[0].front().x, a[0].front().y)->type != 0 )
        std::cerr << " regenerating chunk " << a[0].front().x << "," << a[0].front().y << "|" << world->get(a[0].front().x, a[0].front().y)->type << std::endl;
      a[0].pop();
    }


    while ( ! s[0].empty() )
      chunks->push( s[0].first() );

    std::this_thread::sleep_for( std::chrono::milliseconds( GENERATOR_SLEEP ) );

    chunks->untilEmpty();
  }
}