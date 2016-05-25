#ifndef WINDOW_
#define WINDOW_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "world.hpp"

void drawWorld( sf::RenderWindow& window, World& world );
void draw( sf::RenderWindow& window, World& world, sf::RectangleShape& player );
void input( sf::RenderWindow& window );

#endif // WINDOW_