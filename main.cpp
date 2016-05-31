#include <iostream>
#include <thread>
#include <future>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "defaults.hpp"
#include "world.hpp"
#include "generator.hpp"
#include "window.hpp"
using namespace std;
using namespace sf;

int main( int argc, char** argv )
{
  if ( argc > 1 )
    srand( stoi( argv[1] ) );
  else
    srand( 1337 );

  bool running = true;

  RenderWindow window( VideoMode(510,510), "game", Style::Close );
  window.setFramerateLimit(61);

  World world;
  world.size( window.getSize().x / CHUNK_SIZE, window.getSize().y / CHUNK_SIZE);

  RectangleShape player;
  player.setSize( Vector2f( CHUNK_SIZE, CHUNK_SIZE ) );
  player.setPosition( world.size().x / 2 * CHUNK_SIZE, world.size().y / 2 * CHUNK_SIZE );
  player.setFillColor( Color::Black );

  thread generator( ::generate, &world ); // generate function name MUST have '::' in front because of the 'using namespace' statements.

  while ( window.isOpen() )
  {
    input( window, world );
    draw( window, world, player );
  }

  generator.join();

  window.close();
  return false;
}