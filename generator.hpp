#ifndef GENERATOR_
#define GENERATOR_

#include <thread>
#include <condition_variable>
#include "world.hpp"
#include "data_types/entity.hpp"
#include "data_types/queue.hpp"

typedef sf::Vector2<long long> vector2ll;

void generateChunk( World* world, Queue* queue );
std::deque< Queue< vector2ll > > generateSeq( World* world );
void generate( bool* running, World* world, Entity* player, Queue<vector2ll>* chunks, std::condition_variable* cv );

#endif // GENERATOR_