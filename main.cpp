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

  condition_variable generatorNoti;
  Queue<vector2ll> generation;

  // generate function name MUST have '::' in front because of the 'using namespace' statements.
  thread generator( ::generate, &world, &player, &generation, &generatorNoti );

  while ( window.isOpen() )
  {
    input( window, world, player, generation, generatorNoti );
    draw( window, world, player );
  }

  running = false;
  generator.join();

  window.close();
  return false;
}