#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "data_types/entity.hpp"
#include "data_types/queue.hpp"

void input( sf::RenderWindow* window, bool* running, World* world, Entity* player )
{
  sf::Event e;

  while ( window->pollEvent(e) )
  {
    switch ( e.type )
    {
    case sf::Event::Closed:
      *running = false;
      break;

    case sf::Event::TextEntered:
      switch ( e.text.unicode )
      {
      case 119: // w
        player->y--; // move player up
        break;

      case 97: // a
        player->x--; // move player left
        break;

      case 115: // s
        player->y++; // move player down
        break;

      case 100: // d
        player->x++; // move player right
        break;

      default:
        std::cout << e.text.unicode << std::endl;
        break;
      }
    }
  }
}
