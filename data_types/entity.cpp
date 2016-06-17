#include <SFML/Graphics.hpp>
#include "../defaults.hpp"
#include "entity.hpp"

Entity::Entity()
{
  shape = sf::CircleShape( CHUNK_DIAMETER / 2, 6 );
  shape.setRotation(30);
  shape.setPosition(0,0);
  shape.setOrigin( CHUNK_DIAMETER / 2, CHUNK_dIAMETER / 2);
}