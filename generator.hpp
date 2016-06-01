#ifndef GENERATOR_
#define GENERATOR_

#include <thread>
#include <condition_variable>
#include "world.hpp"
#include "data_types/entity.hpp"
#include "data_types/queue.hpp"

typedef sf::Vector2<long long> vector2ll;

// running is true; false when the thread should exit.
// status is true while the thread is doing computation and false when the thread is waiting.
// cv is used to signal the generation algorithm thread that this a chunk has completed.
void generateChunk( bool* running, bool* status, World* world, Queue<vector2ll>* queue, std::condition_variable* cv );
std::deque< Queue< vector2ll > > generateSeq( World* world, Entity* player );
void generate( bool* running, World* world, Entity* player, Queue<vector2ll>* chunks, std::condition_variable* in, std::condition_variable* childs, std::vector<bool>* chunksSt );

#endif // GENERATOR_