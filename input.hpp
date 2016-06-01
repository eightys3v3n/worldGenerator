#ifndef INPUT_
#define INPUT_

#include <condition_variable>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "data_types/entity.hpp"
#include "data_types/queue.hpp"

void input( sf::RenderWindow* window, bool* running, World* world, Entity* player );

#endif // INPUT_