#include <SFML/System.hpp>

#ifndef CHUNK_SIZE
#define CHUNK_SIZE 10 // chunk width 7 height in pixels; chunks are square
#endif // CHUNK_SIZE

// probabilities of being a given type of ground; between 0-99; must not overlap
#ifndef LAND
#define LAND 1
#define LAND_PROB sf::Vector2<double>{ .x = 0, .y = 69 }
#define LAND_GROUPING 0 // percent increase in probability for adjacent land chunks
#endif // LAND

#ifndef WATER
#define WATER 2
#define WATER_PROB sf::Vector2<double>{ .x = 70, .y = 99 }
#define WATER_GROUPING 10 // percent increase in probability for adjacent water chunks
#endif // WATER

#ifndef DEBUG_COLOUR
#define DEBUG_COLOUR Red
#endif // DEBUG_COLOUR

#ifndef BG_COLOUR
#define BG_COLOUR Color(100,100,100)
#endif // BG_COLOUR

// how many chunks away should be generated
#ifndef VIEW_DISTANCE
#define VIEW_DISTANCE 2
#endif // VIEW_DISTANCE

// size of screen based on chunks
#ifndef SCREEN_X
#define SCREEN_X 50
#endif // SCREEN_X
#ifndef SCREEN_Y
#define SCREEN_Y 50
#endif // SCREEN_Y

// the amount of threads to use for chunk generation.
#ifndef THREADS
#define THREADS 4
#endif // THREADS

// a delay for generating a chunk; it makes it easier to see how they are being generated.
#ifndef GENERATION_DELAY
#define GENERATION_DELAY 90 // ms
#endif // GENERATION_DELAY
