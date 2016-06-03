#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "defaults.hpp"
#include "world.hpp"
#include "data_types/entity.hpp"
#include "data_types/queue.hpp"

void drawWorld( sf::RenderWindow* window, World* world, Entity* player )
{
  for ( long long x = -SCREEN_X / 2; x <= SCREEN_X / 2; x++ )
  {
    for ( long long y = -SCREEN_Y / 2; y <= SCREEN_Y / 2; y++ )
    {
      y--; // PAIR 1:these statments make it draw one chunk above the top of the screen, so there is no empty space.

      if ( world->exists( player->x + x, player->y + y ) )
      {
        sf::Vector2f pos;
        pos.x = CHUNK_SIDE * 1.5 * ( x + ( SCREEN_X / 2 ) );

        //std::cerr << x + player->x << "," << y + player->y << ":" << ( x + player->x ) % 2 << std::endl;

        if ( ( x +  player->x ) % 2 == 0 )
          pos.y = CHUNK_dIAMETER * ( y + SCREEN_Y / 2 );
        else
          pos.y = CHUNK_dIAMETER * ( y + SCREEN_Y / 2 ) + CHUNK_dIAMETER / 2;

        world->shape( player->x + x, player->y + y ).setPosition( pos );
        window->draw( world->shape( player->x + x, player->y + y ) );
      }

      y++; // PAIR 1:
    }
  }
}

void draw( sf::RenderWindow* window, World* world, Entity* player )
{
  window->clear( sf::BG_COLOUR );

  drawWorld( window, world, player );
  window->draw( player->shape );

  window->display();
}

