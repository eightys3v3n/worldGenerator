#ifndef ENTITY_TYPE
#define ENTITY_TYPE

#include <SFML/Graphics.hpp>
#include "../defaults.hpp"

class Entity
{
public:
  Entity();

  sf::CircleShape shape;
  long long x = 0;
  long long y = 0;
};

#endif // ENTITY_TYPE