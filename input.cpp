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

        if ( player->x % 2 == 0 )
          player->shape.setPosition( CHUNK_DIAMETER * .75 * SCREEN_X / 2, CHUNK_dIAMETER * SCREEN_Y / 2 );
        else
          player->shape.setPosition( CHUNK_DIAMETER * .75 * SCREEN_X / 2, CHUNK_dIAMETER * SCREEN_Y / 2 + CHUNK_dIAMETER / 2);

        break;

      case 97: // a
        player->x--; // move player left

        if ( player->x % 2 == 0 )
          player->shape.setPosition( CHUNK_DIAMETER * .75 * SCREEN_X / 2, CHUNK_dIAMETER * SCREEN_Y / 2 );
        else
          player->shape.setPosition( CHUNK_DIAMETER * .75 * SCREEN_X / 2, CHUNK_dIAMETER * SCREEN_Y / 2 + CHUNK_dIAMETER / 2);

        break;

      case 115: // s
        player->y++; // move player down

        if ( player->x % 2 == 0 )
          player->shape.setPosition( CHUNK_DIAMETER * .75 * SCREEN_X / 2, CHUNK_dIAMETER * SCREEN_Y / 2 );
        else
          player->shape.setPosition( CHUNK_DIAMETER * .75 * SCREEN_X / 2, CHUNK_dIAMETER * SCREEN_Y / 2 + CHUNK_dIAMETER / 2);

        break;

      case 100: // d
        player->x++; // move player right

        if ( player->x % 2 == 0 )
          player->shape.setPosition( CHUNK_DIAMETER * .75 * SCREEN_X / 2, CHUNK_dIAMETER * SCREEN_Y / 2 );
        else
          player->shape.setPosition( CHUNK_DIAMETER * .75 * SCREEN_X / 2, CHUNK_dIAMETER * SCREEN_Y / 2 + CHUNK_dIAMETER / 2);

        break;

      default:
        std::cout << e.text.unicode << std::endl;
        break;
      }
    }
  }
}
