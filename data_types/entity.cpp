#include <SFML/Graphics.hpp>
#include "../defaults.hpp"
#include "entity.hpp"

Entity::Entity()
{
  shape = sf::CircleShape( CHUNK_DIAMETER / 2, 6 );
}