#include <iostream>
#include <condition_variable>
#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "data_types/entity.hpp"

void input( sf::RenderWindow* window, bool* running, World* world, Entity* player, std::condition_variable* in )
{
  while ( *running )
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
          player.y--; // move player up
          std::cout << "player " << player.x << "," << player.y << std::endl;

          break;

        case 97: // a
          player.x--; // move player left
          std::cout << "player " << player.x << "," << player.y << std::endl;
          //generator.clear();
          generator.push( vector2ll{ player.x, player.y } );
          cv.notify_one();
          break;

        case 115: // s
          player.y++; // move player down
          std::cout << "player " << player.x << "," << player.y << std::endl;
          //generator.clear();
          generator.push( vector2ll{ player.x, player.y } );
          cv.notify_one();
          break;

        case 100: // d
          player.x++; // move player right
          std::cout << "player " << player.x << "," << player.y << std::endl;
          //generator.clear();
          generator.push( vector2ll{ player.x, player.y } );
          cv.notify_one();
          break;

        default:
          std::cout << event.text.unicode << std::endl;
          break;
        }
      }
    }
  }
}
