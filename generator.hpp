#ifndef GENERATOR_
#define GENERATOR_

#include <thread>
#include <condition_variable>
#include "world.hpp"
#include "data_types/entity.hpp"
#include "data_types/queue.hpp"

typedef sf::Vector2<long long> vector2ll;

void generateHeight( World* world, vector2ll& pos );
void generateChunk( World* world, vector2ll& pos );

// running is true; false when the thread should exit.
// status is true while the thread is doing computation and false when the thread is waiting.
// cv is used to signal the generation algorithm thread that this a chunk has completed.
void generationClient( bool* running, World* world, Queue<vector2ll>* queue, Queue<vector2ll>* finQ, Queue<vector2ll>* generating );
std::deque< Queue< vector2ll > > generateSeq( World* world, Entity* player );
void generationServer( bool* running, World* world, Entity* player, Queue<vector2ll>* chunks, Queue<vector2ll>* finChunks, Queue<vector2ll>* generating );

#endif // GENERATOR_