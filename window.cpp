#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "world.hpp"
#include "defaults.hpp"

void drawWorld( sf::RenderWindow& window, World& world )
{
  for ( unsigned int x = 0; x < world.size().x; x++ )
  {
    for ( unsigned int y = 0; y < world.size().y; y++ )
    {
      if ( world.getType(x,y) > 0 )
        window.draw( world.getShape(x,y) );

      else if ( world.getType(x,y) < 0 ) // debug ground type
      {
        world.getShape(x,y).setFillColor( DEBUG_COLOUR );
        window.draw( world.getShape(x,y) );
      }
    }
  }
}

void draw( sf::RenderWindow& window, World& world, sf::RectangleShape& player )
{
  window.clear( sf::Color(100,100,100) );

  drawWorld( window, world );
  window.draw( player );

  window.display();
}

void input( sf::RenderWindow& window, World& world )
{
  sf::Event event;

  while ( window.pollEvent( event) )
  {
    switch ( event.type )
    {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::TextEntered:
        switch ( event.text.unicode )
        {
          case 119: // w
            world.shiftDown(); // move player up
            break;

          case 97: // a
            world.shiftRight(); // move player left
            break;

          case 115: // s
            world.shiftUp(); // move player down
            break;

          case 100: // d
            world.shiftLeft(); // move player right
            break;

          default:
            std::cout << event.text.unicode << std::endl;
        }
    }
  }
}
