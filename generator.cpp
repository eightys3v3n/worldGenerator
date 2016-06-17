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
#include "data_types/heightMap.hpp"

typedef sf::Vector2<unsigned int> vector2ui;
typedef sf::Vector2<long long> vector2ll;
typedef sf::Vector2<double> vector2d;

extern std::mutex stdoutM;

void generateHeight( World* world, vector2ll& pos )
{
  SIDE_LENGTH_TYPE side = HEIGHT_CHUNK_SIZE;

  while ( side >= 1 )
  {
    try
    {
      world->heightData.get( pos.x, pos.y, side );
    }
    catch ( std::string error )
    {
      world->heightData.set( pos.x, pos.y, side, rand() % HEIGHT_RANGE - ( HEIGHT_RANGE / 2 ) );
    }

    side /= 2;
  }
}

void generateChunk( World* world, vector2ll& pos )
{
  int r, type;
  vector2d land = LAND_PROB;
  vector2d water = WATER_PROB;
  std::vector< Chunk* > chunks;

  chunks = surroundingChunks( world, pos.x, pos.y );

  for ( unsigned int c = 0; c < chunks.size(); c++ )
  {
    if ( chunks[c]->type == LAND )
    {
      land.y += LAND_GROUPING;
      water.x += LAND_GROUPING;
    }
    else if ( chunks[c]->type == WATER )
    {
      land.y -= WATER_GROUPING;
      water.y -= WATER_GROUPING;
    }
  }

  r = rand() % 100;

  if ( r >= land.x && r <= land.y )
    type = LAND;
  else if ( r >= water.x && r <= water.y )
    type = WATER;

  world->set( pos.x, pos.y, type );
}

void generationClient( bool* running, World* world, Queue<vector2ll>* queue, Queue<vector2ll>* finQ )
{
  vector2ll pos;

  while ( *running )
  {
    pos = queue->first();

    if ( ! *running )
      break;

    /*if ( world->get( pos.x, pos.y ) != 0 )
      std::cout << "regenerating chunk " << pos.x << "," << pos.y << std::endl;

    if ( world->heightData.generated( pos.x, pos.y ) )
      std::cout << "regenerating height " << pos.x << "," << pos.y << std::endl;*/

    generateChunk( world, pos );
    generateHeight( world, pos );

    std::this_thread::sleep_for( std::chrono::milliseconds( GENERATION_DELAY ) );

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
    if ( ! r )
    {
      if ( ! world->get(x,y)->type )
      {
        s.resize( s.size() + 1 );
        s[ s.size() - 1].push( vector2ll{x,y} );
      }
      continue;
    }

    for ( unsigned int l = 0; l <= r; l++ ) // expand in the x direction
    {
      s.resize( s.size() + 1 );

      if ( ! l )
      {
        if ( ! world->get(x-r, y)->type )
          s[ s.size() - 1 ].push( vector2ll{x-r, y} );

        if ( ! world->get(x+r, y)->type )
          s[ s.size() - 1 ].push( vector2ll{x+r, y} );
      }
      else
      {
        if ( ! world->get(x+r, y-l)->type )
          s[ s.size() - 1 ].push( vector2ll{x+r, y-l} );

        if ( ! world->get(x-r, y-l)->type )
          s[ s.size() - 1 ].push( vector2ll{x-r, y-l} );

        if ( ! world->get(x+r, y+l)->type )
          s[ s.size() - 1 ].push( vector2ll{x+r, y+l} );

        if ( ! world->get(x-r, y+l)->type )
          s[ s.size() - 1 ].push( vector2ll{x-r, y+l} );
      }

      if ( ! s[ s.size() - 1 ].size() )
        s.resize( s.size() - 1 );
    }

    for ( unsigned int l = 0; l < r; l++ ) // expand in the y direction
    {
      s.resize( s.size() + 1 );

      if ( ! l )
      {
        if ( ! world->get(x, y-r)->type )
          s[ s.size() - 1 ].push( vector2ll{x, y-r} );

        if ( ! world->get(x, y+r)->type )
          s[ s.size() - 1 ].push( vector2ll{x, y+r} );
      }
      else
      {
        if ( ! world->get(x-l, y+r)->type )
          s[ s.size() - 1 ].push( vector2ll{x-l, y+r} );

        if ( ! world->get(x-l, y-r)->type )
          s[ s.size() - 1 ].push( vector2ll{x-l, y-r} );

        if ( ! world->get(x+l, y+r)->type )
          s[ s.size() - 1 ].push( vector2ll{x+l, y+r} );

        if ( ! world->get(x+l, y-r)->type )
          s[ s.size() - 1 ].push( vector2ll{x+l, y-r} );
      }

      if ( ! s[ s.size() - 1 ].size() )
        s.resize( s.size() - 1 );
    }
  }

  return s;
}

void generationServer( bool* running, World* world, Entity* player, Queue<vector2ll>* chunks, std::condition_variable* in, Queue<vector2ll>* finChunks )
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

    std::deque< Queue< vector2ll > > a = generateSeq( world, player );
    while ( ! a[0].empty() )
    {
      if ( world->get( a[0].front().x, a[0].front().y )->type != 0 )
        std::cout << "re-generating chunk " << a[0].front().x << "," << a[0].front().y << std::endl;
      a[0].pop();
    }

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