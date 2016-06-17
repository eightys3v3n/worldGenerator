#include <SFML/Graphics.hpp>

// size of screen based on chunks
#ifndef SCREEN_X
#define SCREEN_X 32
#endif // SCREEN_X
#ifndef SCREEN_Y
#define SCREEN_Y 28
#endif // SCREEN_Y

// height map chunk size
#ifndef HEIGHT_CHUNK_SIZE
#define HEIGHT_CHUNK_SIZE 128
#endif // HEIGHT_CHUNK_SIZE

// 2x the amount an adjacent block can move up or down.
#ifndef HEIGHT_RANGE
#define HEIGHT_RANGE 3
#endif // HEIGHT_RANGE

// the chunk width & height
#ifndef CHUNK_SIZE
#define CHUNK_SIZE 16
#endif // CHUNK_SIZE

// how many chunks away should be generated
#ifndef VIEW_DISTANCE
#define VIEW_DISTANCE 4
#endif // VIEW_DISTANCE

// the amount of threads to use for chunk generation.
#ifndef THREADS
#define THREADS 4
#endif // THREADS

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

// a delay for generating a chunk; it makes it easier to see how they are being generated.
#ifndef GENERATION_DELAY
#define GENERATION_DELAY 40 // ms
#endif // GENERATION_DELAY
