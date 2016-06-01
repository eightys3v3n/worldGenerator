#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "../data_types/queue.cpp"
using namespace std;
using namespace chrono;

bool running = true;
Queue<int> qq;

void produceF()
{
  for ( unsigned int i = 0; i < 20; i++ )
  {
    cout << "pushing " << i << endl;
    qq.push(i);
    this_thread::sleep_for( milliseconds(100) );
    //cout << "pushed input" << endl
  }

  running = false;
}

void consumeF(int id)
{
  while ( running )
  {
    while ( ! qq.empty() )
    {
      cout << "pop" << id << ":" << qq.first() << endl;
      this_thread::sleep_for( milliseconds(400) );
    }
  }
}

int main()
{
  qq.clear();

  cout << "starting consumer" << endl;
  thread consume( consumeF, 0 );
  thread consume1( consumeF, 1 );
  thread consume2( consumeF, 2 );
  thread consume3( consumeF, 3 );

  cout << "starting producer" << endl;
  thread produce( produceF );

  consume.join();
  consume1.join();
  consume2.join();
  consume3.join();
  produce.join();

  return false;
}