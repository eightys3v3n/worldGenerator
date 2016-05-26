#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

#define LEVELS 2
#define CHUNKS 4

struct ChunkQueue
{
  promise< int > p;
  future< int > f = p.get_future();
  vector< future< int >* > r;
};

void func( int l, vector< ChunkQueue >* chunks )
{
  for ( unsigned int c = 0; c < chunks->size(); c++ )
  {
    for ( unsigned int r = 0; r < chunks->at(c).r.size(); r++ )
    {
      cout << "waiting for requisite " << l << ":" << r << endl;
      chunks->at(c).r[r]->wait();
    }

    this_thread::sleep_for( seconds(1) );

    chunks->at(c).p.set_value(true);
    cout << "finished chunk " << l << ":" << c << endl;
  }
}

int main()
{
  vector< vector< ChunkQueue > > sequence;

  sequence.resize( LEVELS );
  for ( unsigned int l = 0; l < sequence.size(); l++ )
    sequence[l].resize( CHUNKS );

  // sets all levels to have the previous level as requisites.
  for ( unsigned int l = 1; l < sequence.size(); l++ )
    for ( unsigned int c = 0; c < sequence[l].size(); c++ )
      for ( unsigned int r = 0; r < sequence[l-1].size(); r++ )
        sequence[l][c].r.push_back( &sequence[l-1][r].f );

  vector< thread > threads;

  // starts all the threads.
  for ( unsigned int l = 0; l < sequence.size(); l++ )
  {
    threads.resize( threads.size() + 1 );
    threads[ threads.size() - 1 ] = thread( func, l, &sequence[l] );
  }

  for ( auto& t : threads )
    t.join();

  return false;
}