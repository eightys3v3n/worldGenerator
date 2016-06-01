#include <iostream>
#include <thread>
#include <future>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "defaults.hpp"
#include "input.hpp"
#include "draw.hpp"
#include "world.hpp"
#include "generator.hpp"
#include "data_types/entity.hpp"
#include "data_types/queue.hpp"
using namespace std;
using namespace sf;

typedef sf::Vector2<long long> vector2ll;

bool running = true;

int main( int argc, char** argv )
{
  if ( argc > 1 )
    srand( stoi( argv[1] ) );
  else
    srand( 1337 );


  RenderWindow window( VideoMode( CHUNK_SIZE * SCREEN_X, CHUNK_SIZE * SCREEN_Y), "game", Style::Close );
  window.setFramerateLimit(31);

  World world;

  Entity player;
  player.shape.setSize( Vector2f( CHUNK_SIZE, CHUNK_SIZE ) );
  player.shape.setPosition(250,250);
  player.shape.setFillColor( Color::Black );
  player.x = 0;
  player.y = 0;

  // create an event embedded in the drawing thread that checks for un-generated chunks?
  condition_variable generationCV;

  // signals when window is available for use of another thread.
  condition_variable windowCV;

  // chunk generation sequence algorithm places chunks in this array that can be safely generated in parallel.
  // it then waits until the array is empty before placing the next set of chunks inside.
  // the chunk generator threads read which chunks to generate from this array.
  Queue<vector2ll> chunksToGen;

  // used to pass events from the drawing thread to the input thread.
  Queue<sf::Event> events;

  cerr << "started input thread" << endl;

  // generate function name MUST have '::' in front because of the 'using namespace' statements.
  // read from chunksToGen and actually generate chunks.
  thread chunkAlgoT( ::generate, &running, &world, &player, &chunksToGen, &generationCV );

  cerr << "started chunk algorithm thread" << endl;

  vector<thread> chunkGenT;

  for ( unsigned int t = 0; t < THREADS; t++ )
    chunkGenT.push_back( thread( generateChunk, &running, &world, &chunksToGen ) );

  cerr << "started chunk generation threads" << endl;

  // starts a loop as long as running == true.
  while ( running )
  {
    input( &window, &running, &world, &player );
    draw( &window, &world, &player );
  }

  cerr << "exiting" << endl;

  // begin exit sequence
  // when running == false draw() will return and all threads should stop shortly.


  if ( window.isOpen() )
    window.close();

  chunkAlgoT.join();

  for ( auto& t : chunkGenT )
    t.join();

  return false;
}