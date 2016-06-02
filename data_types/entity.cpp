#include <SFML/Graphics.hpp>
#include "../defaults.hpp"
#include "entity.hpp"

Entity::Entity()
{
  shape = sf::CircleShape( CHUNK_SIZE / 2, 6 );
}