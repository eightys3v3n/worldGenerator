#include <SFML/Graphics.hpp>
#include "../defaults.hpp"
#include "entity.hpp"

Entity::Entity()
{
  shape.setSize( sf::Vector2f{ CHUNK_SIZE, CHUNK_SIZE } );
  shape.setPosition(0,0);
    shape.setOrigin( CHUNK_SIZE / 2, CHUNK_SIZE / 2);
}