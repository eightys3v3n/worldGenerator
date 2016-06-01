#ifndef WINDOW_
#define WINDOW_

#include <condition_variable>
#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "data_types/entity.hpp"
#include "data_types/queue.hpp"

void drawWorld( sf::RenderWindow& window, World& world, Entity& player );
void draw( sf::RenderWindow* window, World* world, Entity* player );

#endif // WINDOW_