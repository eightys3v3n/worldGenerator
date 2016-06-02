#include <SFML/Graphics.hpp>
#include "../defaults.hpp"
#include "entity.hpp"

Entity::Entity()
{
  shape = sf::CircleShape( CHUNK_SIZE_H, 6 );
}