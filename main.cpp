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

  // signals when a chunk is finished generating.
  condition_variable chunkGensCV;

  // chunk generation sequence algorithm places chunks in this array that can be safely generated in parallel.
  // it then waits until the array is empty before placing the next set of chunks inside.
  // the chunk generator threads read which chunks to generate from this array.
  Queue<vector2ll> chunksToGen;

  // chunks are moved from chunksToGen to here once they are finished.
  Queue<vector2ll> generatedChunks;

  // used to pass events from the drawing thread to the input thread.
  Queue<sf::Event> events;

  // contains all the chunk generating threads.
  vector<thread> chunkGenT;

  // generate function name MUST have '::' in front because of the 'using namespace' statements.
  // read from chunksToGen and actually generate chunks.
  thread chunkAlgoT( ::generate, &running, &world, &player, &chunksToGen, &generationCV, &generatedChunks );


  for ( unsigned int t = 0; t < THREADS; t++ )
    chunkGenT.push_back( thread( generateChunk, &running, &world, &chunksToGen, &generatedChunks ) );

  // starts a loop as long as running == true.
  while ( running )
  {
    //cerr << chunksToGen.size() << " chunks to generate." << endl;
    cerr << generatedChunks.size() << " chunks generated." << endl;

    input( &window, &running, &world, &player );
    draw( &window, &world, &player );
  }


  // begin exit sequence
  // when running == false draw() will return and all threads should stop shortly.
  cerr << "exiting" << endl;

  if ( window.isOpen() )
    window.close();

  cerr << "waiting for chunk algorithm" << endl;
  chunkAlgoT.join();

  cerr << "waiting for chunk generators" << endl;
  for ( auto& t : chunkGenT )
    t.join();

  return false;
}