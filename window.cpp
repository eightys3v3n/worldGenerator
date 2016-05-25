#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "world.hpp"

void drawWorld( sf::RenderWindow& window, World& world )
{
  for ( unsigned int x = 0; x < world.size().x; x++ )
    for ( unsigned int y = 0; y < world.size().y; y++ )
      window.draw( world.getShape(x,y) );
}

void draw( sf::RenderWindow* window, World& world, sf::RectangleShape& player )
{
  window.clear( sf::Color::Black );

  drawWorld( window, world );
  window.draw( player );

  window.display();
}

void input( sf::RenderWindow& window )
{
  sf::Event event;

  while ( window.pollEvent( event) )
  {
    switch ( event.type )
    {
      case sf::Event::Closed:
        window.close();
        break;
    }
  }
}