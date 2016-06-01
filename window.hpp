#ifndef WINDOW_
#define WINDOW_

#include <vector>
#include <condition_variable>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "world.hpp"
#include "data_types/entity.hpp"
#include "data_types/queue.hpp"

typedef sf::Vector2<long long> vector2ll;

void drawWorld( sf::RenderWindow& window, World& world );
void draw( sf::RenderWindow& window, World& world, Entity& player );
void input( sf::RenderWindow& window, World& world, Entity& player, Queue<vector2ll>& generator, std::condition_variable& cv );

#endif // WINDOW_