#include <iostream>
#include <vector>
#include <map>
#include <condition_variable>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "defaults.hpp"
#include "world.hpp"
#include "data_types/entity.hpp"
#include "data_types/queue.hpp"
#include "generator.hpp"

void drawWorld( sf::RenderWindow& window, World& world, Entity& player )
{
  for ( long long x = -SCREEN_X / 2; x <= SCREEN_X / 2; x++ )
  {
    for ( long long y = -SCREEN_X / 2; y <= SCREEN_Y / 2; y++ )
    {
      if ( world.exists( player.x + x, player.y + y ) )
      {
        world.shape( player.x + x, player.y + y ).setPosition( CHUNK_SIZE * ( x + (int)SCREEN_X / 2 ), CHUNK_SIZE * ( y + (int)SCREEN_Y / 2 ) );
        //std::cout << "drawing " << x << "," << y << " @ " << world.shape( player.x + x, player.y + y).getPosition().x << "," << world.shape( player.x + x, player.y + y ).getPosition().y << std::endl;
        window.draw( world.shape( player.x + x, player.y + y ) );
      }
    }
  }
}

void draw( sf::RenderWindow& window, World& world, Entity& player )
{
  window.clear( sf::Color(100,100,100) );

  drawWorld( window, world, player );
  window.draw( player.shape );

  window.display();
}

void input( sf::RenderWindow& window, World& world, Entity& player, Queue<vector2ll>& generator, std::condition_variable& cv )
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
            //generator.clear();
            generator.push( vector2ll{ player.x, player.y } );
            cv.notify_one();
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
        }
    }
  }
}
