#ifndef GENERATOR_
#define GENERATOR_

#include <thread>
#include <condition_variable>
#include "world.hpp"
#include "data_types/entity.hpp"
#include "data_types/queue.hpp"

typedef sf::Vector2<long long> vector2ll;

void generateChunk( World* world, Queue* queue );
void generate( World* world, Entity* player, Queue<vector2ll>* q, std::condition_variable* cv );

#endif // GENERATOR_