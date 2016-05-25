#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "world.hpp"

void drawWorld( sf::RenderWindow& window, World& world )
{
  for ( int x = 0; x < world.size().x; x++ )
  {
    for ( int y = 0; y < world.size().y; y++ )
    {
      window.draw( world.getShape(x,y) );
    }
  }
}

void draw( sf::RenderWindow& window, World& world )
{
  window.clear( sf::Color::Black );

  drawWorld( window, world );

  window.display();
}