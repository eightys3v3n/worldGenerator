#include <iostream>
#include <thread>
#include <future>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "defaults.hpp"
#include "world.hpp"
#include "generator.hpp"
#include "window.hpp"
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

  // used to signal inputT that it should get and process input.
  // used to limit the rate of window.pollEvent() calls to the framerate.
  condition_variable inputCV;

  // generate function name MUST have '::' in front because of the 'using namespace' statements.
  thread generationT( ::generate, &world, &player, &generation, &generationCV );

  // chunk generation sequence algorithm places chunks in this array that can be safely generated in parallel.
  // it then waits until the array is empty before placing the next set of chunks inside.
  // the chunk generator threads read which chunks to generate from this array.
  Queue<vector2ll> chunksToGen;

  // retrieves and processes window events (user input).
  thread inputT( input, &window, &running, &world, &player, &inputCV );

  thread chunkAlgoT( generate, &running, &world, &player, &chunksToGen, &generationCV );

  vector<thread> chunkGenT;

  for ( unsigned int t = 0; t < THREADS; t++ )
    chunkGenT.push_back( thread( generateChunk, &world, &chunksToGen ) );

  // starts a loop as long as running == true.
  draw( &window, &running, &world, &player, &inputCV );


  // begin exit sequence
  // when running == false draw() will return and all threads should stop shortly.


  inputT.join();
  chunkAlgoT.join();

  for ( auto& t : chunkGenT )
    t.join();

  if ( window.isOpen() )
    window.close();

  return false;
}