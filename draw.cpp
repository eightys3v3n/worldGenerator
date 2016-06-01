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
    for ( long long y = -SCREEN_X / 2; y <= SCREEN_Y / 2; y++ )
    {
      if ( world->exists( player->x + x, player->y + y ) )
      {
        world->shape( player->x + x, player->y + y ).setPosition( CHUNK_SIZE * ( x + SCREEN_X / 2 ), CHUNK_SIZE * ( y + SCREEN_Y / 2 ) );
        window->draw( world->shape( player->x + x, player->y + y ) );
      }
    }
  }
}

void draw( sf::RenderWindow* window, World* world, Entity* player )
{
  window->clear( sf::BACKGROUND_COLOUR );

  drawWorld( window, world, player );
  window->draw( player->shape );

  window->display();
}

