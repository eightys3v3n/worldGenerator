#include <iostream>
#include <vector>
#include "world.hpp"
#include "chunk.hpp"

namespace test
{

void printChunks( std::vector< Chunk > chunks )
{
  std::cout << chunks[0].type << "|" << chunks[1].type << "|" << chunks[2].type << std::endl;
  std::cout << "-----" << std::endl;
  std::cout << chunks[3].type << "| |" << chunks[4].type << std::endl;
  std::cout << "-----" << std::endl;
  std::cout << chunks[5].type << "|" << chunks[6].type << "|" << chunks[7].type << std::endl;
  std::cout << "-----" << std::endl;
}

void surroundingChunks( World& world )
{
  std::vector< Chunk > chunks;

  std::cerr << "surroundingChunks:" << std::endl;

  world.size(3,3);
  for ( unsigned int x = 0; x < world.size().x; x++ )
    for ( unsigned int y = 0; y < world.size().y; y++ )
      world.set( x,y, 1);

  std::cerr << " configured world." << std::endl;

  for ( unsigned int x = 0; x < world.size().x; x++ )
  {
    for ( unsigned int y = 0; y < world.size().y; y++ )
    {
      try
      {
        chunks = surroundingChunks( world, x,y);
      }
      catch ( std::string* error )
      {
        throw new std::string( "test::surroundingChunks:" + *error );
      }

      if ( chunks.size() != 8 )
        throw new std::string("surrounding chunks did not return 8 chunks @ " + std::to_string(x) + "," + std::to_string(y) + "." );

      // yes i am aware this code looks like crap; i couldn't think of a nice way of doing it and the alternative
      // was having 9 if statments.
      switch (x)
      {
        case 0:
          switch (y)
          {
            case 0:
              if ( chunks[0].type != 0 || chunks[1].type != 0 || chunks[2].type != 0 ||
                   chunks[3].type != 0                        || chunks[4].type != 1 ||
                   chunks[5].type != 0 || chunks[6].type != 1 || chunks[7].type != 1 )
              {
                printChunks( chunks );
                throw new std::string("test::surroundingChunks:incorrect surrounding chunks for " +
                  std::to_string(x) + "," + std::to_string(y) + "." );
              }
              break;

            case 1:
              if ( chunks[0].type != 0 || chunks[1].type != 1 || chunks[2].type != 1 ||
                   chunks[3].type != 0                        || chunks[4].type != 1 ||
                   chunks[5].type != 0 || chunks[6].type != 1 || chunks[7].type != 1 )
              {
                printChunks( chunks );
                throw new std::string("test::surroundingChunks:incorrect surrounding chunks for " +
                  std::to_string(x) + "," + std::to_string(y) + "." );
              }
              break;

            case 2:
              if ( chunks[0].type != 0 || chunks[1].type != 1 || chunks[2].type != 1 ||
                   chunks[3].type != 0                        || chunks[4].type != 1 ||
                   chunks[5].type != 0 || chunks[6].type != 0 || chunks[7].type != 0 )
              {
                printChunks( chunks );
                throw new std::string("test::surroundingChunks:incorrect surrounding chunks for " +
                  std::to_string(x) + "," + std::to_string(y) + "." );
              }
              break;
          }
          break;

        case 1:
          switch (y)
          {
            case 0:
              if ( chunks[0].type != 0 || chunks[1].type != 0 || chunks[2].type != 0 ||
                   chunks[3].type != 1                        || chunks[4].type != 1 ||
                   chunks[5].type != 1 || chunks[6].type != 1 || chunks[7].type != 1 )
              {
                printChunks( chunks );
                throw new std::string("test::surroundingChunks:incorrect surrounding chunks for " +
                  std::to_string(x) + "," + std::to_string(y) + "." );
              }
              break;

            case 1:
              if ( chunks[0].type != 1 || chunks[1].type != 1 || chunks[2].type != 1 ||
                   chunks[3].type != 1                        || chunks[4].type != 1 ||
                   chunks[5].type != 1 || chunks[6].type != 1 || chunks[7].type != 1 )
              {
                printChunks( chunks );
                throw new std::string("test::surroundingChunks:incorrect surrounding chunks for " +
                  std::to_string(x) + "," + std::to_string(y) + "." );
              }
              break;

            case 2:
              if ( chunks[0].type != 1 || chunks[1].type != 1 || chunks[2].type != 1 ||
                   chunks[3].type != 1                        || chunks[4].type != 1 ||
                   chunks[5].type != 0 || chunks[6].type != 0 || chunks[7].type != 0 )
              {
                printChunks( chunks );
                throw new std::string("test::surroundingChunks:incorrect surrounding chunks for " +
                  std::to_string(x) + "," + std::to_string(y) + "." );
              }
              break;
          }
          break;

        case 2:
          switch (y)
          {
            case 0:
              if ( chunks[0].type != 0 || chunks[1].type != 0 || chunks[2].type != 0 ||
                   chunks[3].type != 1                        || chunks[4].type != 0 ||
                   chunks[5].type != 1 || chunks[6].type != 1 || chunks[7].type != 0 )
              {
                printChunks( chunks );
                throw new std::string("test::surroundingChunks:incorrect surrounding chunks for " +
                  std::to_string(x) + "," + std::to_string(y) + "." );
              }
              break;

            case 1:
              if ( chunks[0].type != 1 || chunks[1].type != 1 || chunks[2].type != 0 ||
                   chunks[3].type != 1                        || chunks[4].type != 0 ||
                   chunks[5].type != 1 || chunks[6].type != 1 || chunks[7].type != 0 )
              {
                printChunks( chunks );
                throw new std::string("test::surroundingChunks:incorrect surrounding chunks for " +
                  std::to_string(x) + "," + std::to_string(y) + "." );
              }
              break;

            case 2:
              if ( chunks[0].type != 1 || chunks[1].type != 1 || chunks[2].type != 0 ||
                   chunks[3].type != 1                        || chunks[4].type != 0 ||
                   chunks[5].type != 0 || chunks[6].type != 0 || chunks[7].type != 0 )
              {
                printChunks( chunks );
                throw new std::string("test::surroundingChunks:incorrect surrounding chunks for " +
                  std::to_string(x) + "," + std::to_string(y) + "." );
              }
              break;
          }
          break;
      }

      std::cerr << " " << x << "," << y << " passed." << std::endl;
    }
  }
}

}