#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "world.hpp"
#include "generator.hpp"
#include "window.hpp"
#include "world.hpp"
using namespace std;
using namespace sf;

int main( int argc, char** argv )
{
  if ( argc > 1 )
    srand( stoi( argv[1] ) );
  else
    srand( 1337 );

  RenderWindow window( VideoMode(500,500), "game", Style::Close );
  window.setFramerateLimit(61);

  World world;
  world.size( window.getSize().x / CHUNK_SIZE, window.getSize().y / CHUNK_SIZE);

  RectangleShape player;
  player.setSize( Vector2f( CHUNK_SIZE, CHUNK_SIZE ) );
  player.setPosition( world.size().x / 2 * 10, world.size().y / 2 * 10 );
  player.setFillColor( Color::Black );

  generate( world );

  while ( window.isOpen() )
  {
    input( window );
    draw( window, world, player );
  }

  window.close();
  return false;
}