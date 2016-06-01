#ifndef ENTITY_TYPE
#define ENTITY_TYPE

#include <SFML/Graphics.hpp>

class Entity
{
public:
  sf::RectangleShape shape;
  long long x = 0;
  long long y = 0;
};

#endif // ENTITY_TYPE